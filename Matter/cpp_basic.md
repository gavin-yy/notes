
## 单例模式(Singletone)

定义一个单例类：

1. 私有化它的构造函数，以防止外界创建单例类的对象；
2. 使用类的私有静态指针变量指向类的唯一实例；
3. 使用一个公有的静态方法获取该实例。

C++11规定了local static在多线程条件下的初始化行为，要求编译器保证了内部静态变量的线程安全性。
在C++11标准下，《Effective C++》提出了一种更优雅的单例模式实现，使用函数内的 local static 对象。
这样，只有当第一次访问getInstance()方法时才创建实例。这种方法也被称为Meyers' Singleton

Matter例子:
```
class DeviceControllerFactory
{
public:
    static DeviceControllerFactory & GetInstance()  //3.公有静态方法获取实例
    {
        static DeviceControllerFactory instance;    //2.静态唯一实例
        return instance;
    }
    
    //....
    
    DeviceControllerFactory(DeviceControllerFactory const &) = delete;
    void operator=(DeviceControllerFactory const &) = delete;
    
private:
    DeviceControllerFactory(){};        //1. 私有化构造函数，以防止外界创建单例类的对象；
}

//使用:
err = DeviceControllerFactory::GetInstance().Init(factoryInitParams);
```

## delegate回调

类似C中的回调函数，回调函数在一个类中实现
```
//定义delegate类，包含所有的回调函数声明. 作为类的虚函数.
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

//包含Delegate指针成员，触发回调函数执行.
class ChipDeviceScanner
{
    //...
    ChipDeviceScannerDelegate * mDelegate = nullptr;  //构造函数 初始化的时候赋值
}

///构造函数，为delegate赋值
ChipDeviceScanner::ChipDeviceScanner(GDBusObjectManager * manager, BluezAdapter1 * adapter, GCancellable * cancellable,
                                     ChipDeviceScannerDelegate * delegate) :
    mManager(manager),
    mAdapter(adapter), mCancellable(cancellable), mDelegate(delegate)   //为mDelegate赋值
{       
}

//继承delegate类，实现delegate函数
class BLEManagerImpl final : private ChipDeviceScannerDelegate
                             
//具体实现类，
void BLEManagerImpl::InitiateScan(BleScanState scanType)
{
    //创建扫描类，回调函数在本类中定义,delegate=this    
    mDeviceScanner               = Internal::ChipDeviceScanner::Create(mpEndpoint->mpAdapter, this);
}
```
