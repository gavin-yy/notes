
## 配网

```plantuml
class command {
    //管理命令行
    -std::map<std::string, CommandsVector> mClusters; 
    
    //commissioner控制
    -chip::Controller::DeviceCommissioner mController;
    -chip::Controller::ExampleOperationalCredentialsIssuer mOpCredsIssuer;
    
    //存储
    -PersistentStorage mStorage;
}
```

```c
commands::run(int argc, char **argv)
{
    //1.平台初始化
    err = chip::Platform::MemoryInit();
    
    //2.蓝牙初始化，作为主控端
    err = chip::DeviceLayer::Internal::BLEMgrImpl().ConfigureBle(/* BLE adapter ID */ 0,
             /* BLE central */ true);
    
    //3. 读取存储的网络等信息
    chip::Logging::SetLogFilter(mStorage.GetLoggingLevel());
    localId  = mStorage.GetLocalNodeId();
    remoteId = mStorage.GetRemoteNodeId();
    
    //4.出厂默认参数
    factoryInitParams.storageDelegate = &mStorage;
    factoryInitParams.listenPort      = mStorage.GetListenPort();
    
    //5.证书相关信息
    err = mOpCredsIssuer.Initialize(mStorage);
    
    chip::Credentials::SetDeviceAttestationCredentialsProvider(chip::Credentials::Examples::GetExampleDACProvider());
    chip::Credentials::SetDeviceAttestationVerifier(chip::Credentials::Examples::GetExampleDACVerifier());

    VerifyOrExit(rcac.Alloc(chip::Controller::kMaxCHIPDERCertLength), err = CHIP_ERROR_NO_MEMORY);
    VerifyOrExit(noc.Alloc(chip::Controller::kMaxCHIPDERCertLength), err = CHIP_ERROR_NO_MEMORY);
    VerifyOrExit(icac.Alloc(chip::Controller::kMaxCHIPDERCertLength), err = CHIP_ERROR_NO_MEMORY);
    
     //6. init the factory, then setup the Controller
    err = DeviceControllerFactory::GetInstance().Init(factoryInitParams); //->InitSystemState(params);
    VerifyOrExit(err == CHIP_NO_ERROR, ChipLogError(Controller, "Controller Factory failed to initialize"));

    //6.2 SetupCommissioner
    commissionerParams.ephemeralKeypair = &ephemeralKey;
    commissionerParams.controllerRCAC   = rcacSpan;
    commissionerParams.controllerICAC   = icacSpan;
    commissionerParams.controllerNOC    = nocSpan;
    err = DeviceControllerFactory::GetInstance().SetupCommissioner(commissionerParams, mController);
    VerifyOrExit(err == CHIP_NO_ERROR, ChipLogError(Controller, "Init failure! Commissioner: %s", chip::ErrorStr(err)));
    
    //7. seperate eventloop if enabled.
    err = DeviceControllerFactory::GetInstance().ServiceEvents();
    
    //8. 执行命令
    err = RunCommand(localId, remoteId, argc, argv, &command);
    
    //9. eventloop 结束
    chip::DeviceLayer::PlatformMgr().StopEventLoopTask();
    
}
```

//对协议栈的各层进行初始化
CHIP_ERROR DeviceControllerFactory::InitSystemState(FactoryInitParams params)
{
    DeviceControllerSystemStateParams stateParams;
    
    ReturnErrorOnFailure(DeviceLayer::PlatformMgr().InitChipStack());
    stateParams.systemLayer = &DeviceLayer::SystemLayer();
    stateParams.inetLayer   = &DeviceLayer::InetLayer;
    stateParams.bleLayer = DeviceLayer::ConnectivityMgr().GetBleLayer();
    
    //初始化传输层
    ReturnErrorOnFailure(stateParams.transportMgr->Init(
        Transport::UdpListenParameters(stateParams.inetLayer).SetAddressType(Inet::kIPAddressType_IPv6).SetListenPort(mListenPort)
#if INET_CONFIG_ENABLE_IPV4
            ,
        Transport::UdpListenParameters(stateParams.inetLayer).SetAddressType(Inet::kIPAddressType_IPv4).SetListenPort(mListenPort)
#endif
#if CONFIG_NETWORK_LAYER_BLE
            ,
        Transport::BleListenParameters(stateParams.bleLayer)
#endif
            ));

    ReturnErrorOnFailure(stateParams.fabricTable->Init(mStorageDelegate));
    ReturnErrorOnFailure(
        stateParams.sessionMgr->Init(stateParams.systemLayer, stateParams.transportMgr, stateParams.messageCounterManager));
    ReturnErrorOnFailure(stateParams.exchangeMgr->Init(stateParams.sessionMgr));
    ReturnErrorOnFailure(stateParams.messageCounterManager->Init(stateParams.exchangeMgr));
}


配对命令:PairingCommand.cpp
CHIP_ERROR PairingCommand::RunInternal(NodeId remoteId)
{
    case PairingMode::Ble:
        err = Pair(remoteId, PeerAddress::BLE());    //PeerAddress::BLE() 只设置类型: PeerAddress(Type type) : mTransportType(type) {}
        break;
}

CHIP_ERROR PairingCommand::Pair(NodeId remoteId, PeerAddress address)
{
    RendezvousParameters params =
        RendezvousParameters().SetSetupPINCode(mSetupPINCode).SetDiscriminator(mDiscriminator).SetPeerAddress(address);

    return GetExecContext()->commissioner->PairDevice(remoteId, params);
}

CHIPDeviceController.cpp

```c
CHIP_ERROR DeviceCommissioner::PairDevice(NodeId remoteDeviceId, RendezvousParameters & params)
{
    //device列表中，申请一个空闲位置，存储device信息
    mDeviceBeingPaired = GetInactiveDeviceIndex();
    VerifyOrExit(mDeviceBeingPaired < kNumMaxActiveDevices, err = CHIP_ERROR_NO_MEMORY);
    device = &mActiveDevices[mDeviceBeingPaired];  
    
    if (params.HasDiscriminator())
    {
        //根据Discriminator发现设备，并连接
        SuccessOrExit(err = mSystemState->BleLayer()->NewBleConnectionByDiscriminator(params.GetDiscriminator()));
    }  
    
}
```



## 蓝牙扫描、连接

linux/bluez/
ChipDeviceScanner.cpp

```
/// Receives callbacks when chip devices are being scanned
class ChipDeviceScannerDelegate
{
public:
    virtual ~ChipDeviceScannerDelegate() {}

    // Called when a CHIP device was found
    virtual void OnDeviceScanned(BluezDevice1 * device, const chip::Ble::ChipBLEDeviceIdentificationInfo & info) = 0;

    // Called when a scan was completed (stopped or timed out)
    virtual void OnScanComplete() = 0;
};

class ChipDeviceScanner
{
    //...
    ChipDeviceScannerDelegate * mDelegate = nullptr;
}

ChipDeviceScanner::ChipDeviceScanner(GDBusObjectManager * manager, BluezAdapter1 * adapter, GCancellable * cancellable,
                                     ChipDeviceScannerDelegate * delegate) :
    mManager(manager),
    mAdapter(adapter), mCancellable(cancellable), mDelegate(delegate)   //为mDelegate赋值
{
        
}
```

```

std::unique_ptr<ChipDeviceScanner> ChipDeviceScanner::Create(BluezAdapter1 * adapter, ChipDeviceScannerDelegate * delegate)
{
    return std::make_unique<ChipDeviceScanner>(manager.get(), adapter, cancellable.get(), delegate);
}

//mainloop中扫描到设备后，调用delegate中的回调，进入BLEManagerImpl的OnDeviceScanned
void ChipDeviceScanner::SignalObjectAdded(GDBusObjectManager * manager, GDBusObject * object, ChipDeviceScanner * self)
{
    self->ReportDevice(bluez_object_get_device1(BLUEZ_OBJECT(object)));  //对应:mDelegate->OnDeviceScanned(device, deviceInfo);
}
```


```C
void BLEManagerImpl::InitiateScan(BleScanState scanType)
{
    //创建扫描类，回调函数在本类中定义    
    mDeviceScanner               = Internal::ChipDeviceScanner::Create(mpEndpoint->mpAdapter, this);
    
    // 扫描类型 kNotScanning, 
    // kScanForDiscriminator, 扫描后，比较Discriminator，匹配则连接
    // kScanForAddress, 扫描后，比较Discriminator，匹配则连接
    // kConnecting, 连接中
    mBLEScanConfig.mBleScanState = scanType;
    CHIP_ERROR err = mDeviceScanner->StartScan(kNewConnectionScanTimeoutMs);
}

//创建连接函数，扫描，匹配到Discriminator后，进行连接
void BLEManagerImpl::NewConnection(BleLayer * bleLayer, void * appState, const uint16_t connDiscriminator)
{
    mBLEScanConfig.mDiscriminator = connDiscriminator;
    mBLEScanConfig.mAppState      = appState;

    // Scan initiation performed async, to ensure that the BLE subsystem is initialized.
    PlatformMgr().ScheduleWork(InitiateScan, static_cast<intptr_t>(BleScanState::kScanForDiscriminator));
}

void BLEManagerImpl::OnDeviceScanned(BluezDevice1 * device, const chip::Ble::ChipBLEDeviceIdentificationInfo & info)
{
    ChipLogProgress(Ble, "New device scanned: %s", bluez_device1_get_address(device));
}
```

何时触发扫描？ 在src/ble/BleLayer.cpp中 mSystemState->BleLayer()->NewBleConnectionByDiscriminator (上一节所示)
