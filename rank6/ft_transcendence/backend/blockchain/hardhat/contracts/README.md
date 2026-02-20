# 📜 Smart Contracts - TournamentRegistry

## 📋 General Description

This directory contains the **Solidity smart contract** `TournamentRegistry.sol`, which implements an immutable tournament registry system on an Avalanche-compatible blockchain.

## 📄 Main File

```
contracts/
└── TournamentRegistry.sol    # Main contract (236 lines)
```

## 🎯 Contract Purpose

The `TournamentRegistry` contract provides:

- ✅ **Immutable Registry** - Tournament results cannot be modified
- ✅ **Transparency** - Anyone can verify historical results
- ✅ **Traceability** - Blockchain events for complete auditing
- ✅ **Decentralization** - Does not depend on central authorities

## 🏗️ Contract Structure

### Stored Data (Struct)

```solidity
struct TournamentRecord {
    uint256 recordId;           // Unique incremental ID
    string tournamentName;      // Tournament name
    uint256 startTime;          // Start timestamp (block.timestamp)
    uint256 endTime;            // End timestamp
    address champion;           // Winner's address
    address[] players;          // Participant addresses
    uint256[] finalScores;      // Final scores
    string[] playerAliases;     // Player aliases/names
    bool isFinalized;           // true = tournament completed
}
```

### State Variables

```solidity
// Mapping from ID → Full record
mapping(uint256 => TournamentRecord) private tournamentRecords;

// Global tournament counter
uint256 private recordCounter;
```

### Events

```solidity
event TournamentRegistered(
    uint256 indexed recordId,
    string tournamentName,
    uint256 timestamp,
    address indexed registeredBy
);

event TournamentFinalized(
    uint256 indexed recordId,
    address indexed champion,
    uint256 timestamp
);
```

## 🔧 Public Functions

### 1. `registerTournament`

**Purpose:** Registers a new tournament on the blockchain.

```solidity
function registerTournament(
    string memory _name,
    address[] memory _players,
    string[] memory _aliases
) public returns (uint256 newRecordId)
```

**Parameters:**
- `_name` - Tournament name (e.g.: "Summer Cup 2025")
- `_players` - Array of Ethereum addresses of the players
- `_aliases` - Array of aliases/nicknames (must match `_players`)

**Returns:**
- `newRecordId` - ID of the created record

**Validations:**
- ✅ Name is not empty
- ✅ Minimum 2 players
- ✅ Length of `_players` == length of `_aliases`

**Emitted Events:**
- `TournamentRegistered`

**Usage Example:**
```javascript
const tx = await registry.registerTournament(
    "Christmas Tournament 2025",
    ["0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb", "0x8626f6940E2eb28930eFb4CeF49B2d1F2C9C1199"],
    ["Alice", "Bob"]
);
await tx.wait();
```

### 2. `finalizeTournament`

**Purpose:** Marks a tournament as finalized and records the winner.

```solidity
function finalizeTournament(
    uint256 _recordId,
    address _champion,
    uint256[] memory _finalScores
) public
```

**Parameters:**
- `_recordId` - ID of the tournament to finalize
- `_champion` - Winner's address
- `_finalScores` - Final scores of all players

**Validations:**
- ✅ Tournament exists
- ✅ Not already finalized
- ✅ Champion is among the registered players
- ✅ Length of `_finalScores` matches number of players

**Emitted Events:**
- `TournamentFinalized`

**Usage Example:**
```javascript
await registry.finalizeTournament(
    0,  // recordId
    "0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb",  // winner
    [100, 75]  // scores
);
```

### 3. `getTournament`

**Purpose:** Gets the complete information of a tournament.

```solidity
function getTournament(uint256 _recordId) 
    public 
    view 
    returns (TournamentRecord memory)
```

**Parameters:**
- `_recordId` - ID of the tournament to query

**Returns:**
- Full `TournamentRecord` struct

**Usage Example:**
```javascript
const record = await registry.getTournament(0);
console.log("Tournament:", record.tournamentName);
console.log("Winner:", record.champion);
console.log("Players:", record.players);
```

### 4. `getAllTournaments`

**Purpose:** Gets all registered tournaments.

```solidity
function getAllTournaments() 
    public 
    view 
    returns (TournamentRecord[] memory)
```

**Returns:**
- Array with all tournament records

**Note:** ⚠️ This function can be expensive in gas if there are many tournaments. Use with caution.

**Usage Example:**
```javascript
const allTournaments = await registry.getAllTournaments();
console.log(`Total tournaments: ${allTournaments.length}`);
```

### 5. `getTournamentCount`

**Purpose:** Gets the total number of registered tournaments.

```solidity
function getTournamentCount() 
    public 
    view 
    returns (uint256)
```

**Returns:**
- Tournament counter (uint256)

**Usage Example:**
```javascript
const count = await registry.getTournamentCount();
console.log(`Total tournaments: ${count}`);
```

### 6. `getPlayerTournaments`

**Purpose:** Gets all tournaments in which a player participated.

```solidity
function getPlayerTournaments(address _player) 
    public 
    view 
    returns (uint256[] memory)
```

**Parameters:**
- `_player` - Player's address

**Returns:**
- Array of tournament IDs

**Usage Example:**
```javascript
const myAddress = "0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb";
const myTournaments = await registry.getPlayerTournaments(myAddress);
console.log(`Participated in ${myTournaments.length} tournaments`);
```

### 7. `getPlayerStats`

**Purpose:** Gets aggregated statistics for a player.

```solidity
function getPlayerStats(address _player) 
    public 
    view 
    returns (
        uint256 totalTournaments,
        uint256 tournamentsWon,
        uint256 totalScore
    )
```

**Parameters:**
- `_player` - Player's address

**Returns:**
- `totalTournaments` - Tournaments played
- `tournamentsWon` - Tournaments won
- `totalScore` - Total accumulated score

**Usage Example:**
```javascript
const [total, won, score] = await registry.getPlayerStats(playerAddress);
console.log(`Win Rate: ${(won/total*100).toFixed(1)}%`);
console.log(`Total Score: ${score}`);
```

## 🔐 Security

### Modifiers and Validations

```solidity
// ✅ Input validation
require(bytes(_name).length > 0, "Tournament name required");
require(_players.length >= 2, "Minimum 2 players required");

// ✅ State verification
require(!tournamentRecords[_recordId].isFinalized, "Tournament already finalized");

// ✅ Participant validation
bool isValidChampion = false;
for (uint256 i = 0; i < players.length; i++) {
    if (players[i] == _champion) {
        isValidChampion = true;
        break;
    }
}
require(isValidChampion, "Champion must be a registered player");
```

### Gas Considerations

| Operation | Estimated Gas | Optimization |
|-----------|---------------|--------------|
| `registerTournament` | ~150k - 300k | Depends on # of players |
| `finalizeTournament` | ~100k - 200k | Depends on # of scores |
| `getTournament` (view) | 0 gas | Read only |
| `getAllTournaments` (view) | 0 gas | Can be slow with many records |
| `getPlayerStats` | 0 gas | Optimized loop |

### Known Limitations

1. **getAllTournaments()** may fail with many tournaments (gas limit)
   - **Solution:** Use pagination or specific indexes

2. **No record modification** (by design)
   - Finalized tournaments are immutable
   - If there is an error, a new tournament must be registered

3. **No access control** (anyone can register)
   - Considered a feature (decentralized)
   - Backend must validate before writing

## 🧪 Testing

### Recommended Test Cases

```javascript
describe("TournamentRegistry", function () {
  it("Should register a tournament with 2 players", async () => {
    // Basic registration test
  });

  it("Should finalize tournament correctly", async () => {
    // Finalization test
  });

  it("Should revert if champion is not a player", async () => {
    // Validation test
  });

  it("Should track player stats correctly", async () => {
    // Statistics test
  });

  it("Should emit events correctly", async () => {
    // Events test
  });
});
```

## 📊 Backend Integration

The backend interacts with this contract through:

```
backend/blockchain/blockchain-service.js
```

**Integration flow:**
1. User creates tournament in frontend
2. Backend validates data
3. Backend calls `registerTournament()` on the contract
4. Blockchain emits `TournamentRegistered` event
5. Backend saves `recordId` in database
6. When tournament ends → `finalizeTournament()`

## 🔗 Solidity Version

```solidity
// SPDX-License-Identifier: MIT
pragma solidity ^0.8.19;
```

**Features used:**
- Solidity 0.8.19 (latest stable compatible)
- String memory for gas efficiency
- Dynamic arrays in memory
- Complex structs
- Indexed events for fast searching

## 📚 Related Documentation

- [Hardhat Project](../README.md) - Environment configuration
- [Deploy Scripts](../scripts/README.md) - Deployment scripts
- [Blockchain Service](../../README.md) - Backend service

## 🔗 Useful Links

- [Solidity Docs](https://docs.soliditylang.org/)
- [OpenZeppelin Contracts](https://docs.openzeppelin.com/contracts/)
- [Avalanche C-Chain](https://docs.avax.network/learn/avalanche/avalanche-platform)
- [Ethers.js ABI Encoding](https://docs.ethers.org/v6/api/abi/)

---

**📜 TournamentRegistry Smart Contract** - Version 1.0.0  
*Last updated: December 2025*