
## mDNSResponder
local server:
```shell
sudo ./mdnsd -debug
```

client tools:
```shell
./dns-sd --help
dns-sd -E                          (Enumerate recommended registration domains)
dns-sd -F                          (Enumerate recommended browsing     domains)
dns-sd -R <Name> <Type> <Domain> <Port> [<TXT>...]         (Register a service)
dns-sd -P <Name> <Type> <Domain> <Port> <Host> <IP> [<TXT>...] (Register Proxy)
dns-sd -B        <Type> <Domain>                 (Browse for service instances)
dns-sd -Z        <Type> <Domain>           (Output results in Zone File format)
dns-sd -L <Name> <Type> <Domain>        (Resolve (‘lookup’) a service instance)
dns-sd -Q <name> <rrtype> <rrclass>         (Generic query for any record type)
dns-sd -q <name> <rrtype> <rrclass>     (Generic query, using SuppressUnusable)
dns-sd -G v4/v6/v4v6 <hostname>          (Get address information for hostname)
dns-sd -X udp/tcp/udptcp <IntPort> <ExtPort> <TTL>           (NAT Port Mapping)
dns-sd -H                               (Print usage for complete command list)
dns-sd -V            (Get version of currently running daemon / system service)
```

```
./dns-sd_shared -B _heythings._udp local.
Timestamp     A/R    Flags  if Domain               Service Type         Instance Name
2:33:49.525   Add        3   4 local.               _heythings._udp.     JMGO
 ```
 
-L 
Look up and display the information necessary to contact and use the named service. 
This information includes the hostname of the machine where that service is available, 
the port number on which the service is listening, and (if present) TXT record attributes describing properties of the service.

get hostname & TXT info
```
#./dns-sd_shared -L f001 _heythings._udp local.
3:30:05.604  f001._heythings._udp.local. can be reached at blicca-bbf8.local.:18516 (interface 3)
 P=rthL N=3c93aee482d2c00 A=2f62
```

get ip addr provide hostname
```
./dns-sd_shared -G blicca-bbf8.local.
Timestamp     A/R    Flags if Hostname                               Address                                      TTL
3:34:53.171  Add        2  3 blicca-bbf8.local.                     192.168.137.29                               60
```

provide subtype
```
./dns-sd_shared -L 12129.272814047520173056 _heythings._udp,_id local.
subtype: _id._sub._heythings._udp
```
