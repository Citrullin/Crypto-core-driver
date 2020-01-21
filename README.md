# Crypto core module REST server

## Dependency installation

Use [iccfpga-install-scripts](https://gitlab.com/Citrullin/iccfpga-install-scripts) to install the REST server, crypto core flash utils and dependencies.

## API

The API is similar to the [official REST API of IRI](https://docs.iota.org/docs/node-software/0.1/iri/references/api-reference).
It should be possible to point the IOTA libraries to the REST server endpoint instead.
Some commands of the APIs are equal. Because of the nature of the crypto core, there are
some additional commands, which are not available in the official API.

### API HTTP Header

|       Header       |       Value       | Required or Optional |
|--------------------|-------------------|----------------------|
| X-IOTA-API-Version |         1         |        Required      |
| Content-Type       |	application/json |  	  Required      |

### Commands

#### setFlags

**Scope:**
This command is only available in the iccfpga REST server.

**Functional description:**
Currently, a flag can be set to cache the seed read from the secure element for requests. This saves about 1-2s of time per request. The seeds are storded in the internal RAM.

**Request:**
```json
{"command":"setFlags", "flags":{"keepSeedInRAM":true}}
```

**200 Response:**
```json
{"code": 200, "duration": 250}
```

**400 Response:**
```json
{"code": 400, "error": "..."}
```

#### testHardwareAcceleration

**Scope:**
This command is only available in the iccfpga REST server.

**Functional description:**
Tests the hardware acceleration. Type conversions (Bytes <-> Trytes and Bytes <-> Trits) and hashing (PoW, Curl, Keccak384, Troika) are tested and compared with unaccelerated functions or verified correct results.

**Request:**
```json
{"command":"testHardwareAcceleration"}
```

**200 Response:**
```json
{"bytesToTritsSingle":"pass","tritsToBytesSingle":"pass","pow":"pass","keccak384":"pass","bytesToTritsRandomRepeated":"pass","tritsToBytesRandomRepeated":"pass","trytesToBigintRandomRepeated":"pass","bigintToTrytesRandomRepeated":"pass","troika":"pass","curl":"pass","duration":18964,"code":200}
```

**400 Response:**
```json
{"code": 400, "error": "..."}
```

#### generateRandomSeed

**Scope:**
This command is only available in the iccfpga REST server.

**Functional description:**
Generate a random seed and store it in one of eight slots.

**Request:**
```json
{"command":"generateRandomSeed", "key": 0}
```

**200 Response:**
```json
{"code": 200, "duration": 1800}
```

**400 Response:**
```json
{"code": 400, "error": "..."}
```

#### generateAddress

**Scope:**
This command is only available in the iccfpga REST server.

**Functional description:**
Generates `number` addresses starting at index `firstIndex` with Security-Level `security`. It uses the seed stored in `key`.

**Request:**
```json
{"command":"generateAddress", "key": 0, "firstIndex": 0, "number": 10, "security": 2}
```

**200 Response:**
```json
{"code": 200, "duration": 1800, "trytes": ["....","....","..."]}
```

**400 Response:**
```json
{"code": 400, "error": "..."}
```

#### attachToTangle

**Scope:**
This command is also available in the IRI REST API. It should be possible
to point the official IOTA library with this command.

**Functional description:**
Performas attachToTangle with Proof-of-Work. This function is quite restricted because of internal RAM. Only 8 TXs can be attached. Mostly it is better to use the `doPow` command and chain the transactions externally.

**Request:**
```json
{"command":"attachToTangle", "trunkTransaction": "...", "branchTransaction": "...", "minWeightMagnitude": 14, "timestamp": 1552571227826, "trytes": ["....", "....", "..."]}
```

**200 Response:**
```json
{"code": 200, "duration": 1800, "trytes": ["....","....",...]}
```

**400 Response:**
```json
{"code": 400, "error": "..."}
```

#### doPow

**Scope:**
This command is only available in the iccfpga REST server.

**Functional description:**
Do Proof-of-Work on an array of Trytes. Currently up to 10 transactions can be processed at once.

**Request:**
```json
{"command":"doPow","minWeightMagnitude": 14, "trytes": ["....", "....", "..."]}
```

**200 Response:**
```json
{"code": 200, "duration": 1800, "trytes": ["....","....",...]}
```

**400 Response:**
```json
{"code": 400, "error": "..."}
```

#### signTransaction

**Scope:**
This command is only available in the iccfpga REST server.

**Functional description:**
Signs a single transactions and uses `key` as slot for the seed. The field `auth` is calculated this way:
`auth = keccak384(key+addressIndex+bundleHash+apiKey)`

**Request:**
```json
{"command":"signTransaction","key": 0, "addressIndex": 0, "bundleHash": "...", "securityLevel": 2, "auth": "..."}
```

**200 Response:**
```json
{"code": 200, "duration": 1800, "trytes": ["....","....","..."]}
```

**400 Response:**
```json
{"code": 400, "error": "..."}
```

#### jsonDataTX

**Scope:**
This command is only available in the iccfpga REST server.

**Functional description:**
Initializes the secure-Element. **This has to be done once in a secure environment.** The key has to be the same which is saved in the firmware.

**Request:**
```json
{"command": "jsonDataTX","trunkTransaction":"...","branchTransaction":"...","minWeightMagnitude": 14,"tag":"...","address":"...","timestamp":1566907523000,"data":{"test":"narf"}}
```

**200 Response:**
```json
{"code": 200, "duration": 335, "hash":"...9999", "trytes": ["....","....","..."]}
```

**400 Response:**
```json
{"code": 400, "error": "..."}
```

#### initSecureElement

**Request:**
```json
{"code": 200, "duration": 335}
```

**200 Response:**
```json
{"code": 200, "duration": 335}
```

**400 Response:**
```json
{"code": 400, "error": "..."}
```