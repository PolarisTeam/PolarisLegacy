THIS PROJECT HAS BEEN DEPRICATED
====
We now are coding PolarisServer in C# at https://github.com/PolarisTeam/PolarisLegacy. Please clone that repository.
The readme for PolarisLegacy below will remain for archival purposes.

PolarisLegacy Server
====
## Information
We're a PSO2 Private server, very, very WIP.

*Status:* The basic framework is being coded and basic protocol is being worked on. *No it is not playable yet.*

If you'd like to contribute, contact us on [IRC] (irc://irc.badnik.net/pso2) at irc.badnik.net #pso2

Also check out our wiki where protocol documentation will be done: http://pso2proxy.cyberkitsune.net/wiki/

Build Status: [![Build Status](https://travis-ci.org/cyberkitsune/PolarisServer.svg?branch=master)](https://travis-ci.org/cyberkitsune/PolarisServer)

## Building
1. Install libpoco-dev and cmake, along with basic development tools. On Debian based systems:
```
apt-get install libpoco-dev cmake build-essential git
```
2. Clone this repo.
3. `cmake . && make` and hope the build isn't broken.
4. Watch as the server doesn't do anything. AMAZING!
