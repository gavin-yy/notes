
## VM use Host's proxy
   VM is ubuntu, Host is windows, running v2ray as proxy server/
	

##	
fatal: unable to access 'http://github.com/xxx': gnutls_handshake() failed: Error in the pull function.

caused by PROXY

git config --global http.proxy 'socks5://192.168.50.145:1080'
git config --global https.proxy 'socks5://192.168.50.145:1080'

git config --global --unset http.proxy 'socks5://192.168.50.145:1080'
git config --global --unset https.proxy 'socks5://192.168.50.145:1080'

For Most application:
export HTTP_PROXY=socks5://your.proxy.server:port/
export HTTPS_PROXY=socks5://your.proxy.server:port/

For wget only:
For all users of the system via the /etc/wgetrc or for the user only with the ~/.wgetrc file:
use_proxy=yes
http_proxy=http://192.168.50.145:1081  not support sock5
https_proxy=http://192.168.50.145:1081

