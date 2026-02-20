# ⚡ Hardhat - Blockchain Development Environment

## 📋 General Description

This directory contains the complete **Hardhat project** for the development, testing and deployment of the `TournamentRegistry` smart contract on Avalanche-compatible networks.

**Hardhat** is a professional development environment for Ethereum and EVM-compatible blockchains, providing tools to compile, deploy, test and debug smart contracts.

## 🗂️ Project Structure

```
hardhat/
├── hardhat.config.js         # Main Hardhat configuration
├── package.json              # Dependencies and npm scripts
├── contract-address.json     # Deployed contract info (generated)
├── contracts/                # Solidity smart contracts
│   └── TournamentRegistry.sol
├── scripts/                  # Deployment and utility scripts
│   └── deploy.js
├── artifacts/                # Compiled contract files (generated)
│   ├── build-info/          # Compilation metadata
│   └── contracts/           # ABIs and bytecode
└── cache/                    # Hardhat cache (generated)
    └── solidity-files-cache.json
```

## 🚀 Technologies and Dependencies

### Core
- **Hardhat 2.19.4** - Blockchain development framework
- **@nomicfoundation/hardhat-toolbox 4.0.0** - Complete tooling suite

### Toolbox includes:
- **ethers.js v6** - Library for interacting with Ethereum
- **Hardhat Chai Matchers** - Assertions for testing
- **Hardhat Network Helpers** - Testing utilities
- **Hardhat Verify** - Automatic verification on explorers
- **Solidity Coverage** - Test coverage
- **TypeScript** - TypeScript support

## ⚙️ Configuration (hardhat.config.js)

```javascript
{
  solidity: "0.8.19",           // Solidity version
  networks: {
    fuji: {                     // Avalanche Fuji Testnet
      url: "https://api.avax-test.network/ext/bc/C/rpc",
      chainId: 43113,
      accounts: [PRIVATE_KEY]   // Loaded from .env
    },
    hardhat: {                  // Local network for testing
      chainId: 31337
    },
    localhost: {                // Hardhat local node
      url: "http://127.0.0.1:8545"
    }
  }
}
```

### Required Environment Variables

Location: `/sgoinfre/students/sternero/transcendence/srcs/secrets/.env`

```bash
# Wallet private key (NEVER commit this!)
PRIVATE_KEY=0x...

# Avalanche Fuji RPC URL (optional, uses default if not set)
AVALANCHE_RPC_URL=https://api.avax-test.network/ext/bc/C/rpc
```

## 📦 Available Scripts

```bash
# Compile contracts
npm run compile
# → Compiles TournamentRegistry.sol
# → Generates artifacts/ and cache/

# Deploy on local network
npm run deploy
# → Deploys on localhost (hardhat node)

# Deploy on Hardhat Network
npm run deploy:hardhat
# → Deploys on ephemeral testing network

# Start local node
npm run node
# → Starts local blockchain at 0.0.0.0:8545
# → Useful for development and testing

# Run tests
npm run test
# → Runs test suite (if tests exist)

# Clean artifacts
npm run clean
# → Deletes artifacts/ and cache/
```

## 🔧 Practical Usage

### 1. Compile the Contract

```bash
cd backend/blockchain/hardhat
npm install
npm run compile
```

**Expected output:**
```
Compiled 1 Solidity file successfully
```

**Generated files:**
- `artifacts/contracts/TournamentRegistry.sol/TournamentRegistry.json` - ABI + bytecode
- `cache/solidity-files-cache.json` - Compilation cache

### 2. Deploy on Local Network (Development)

**Terminal 1 - Start node:**
```bash
npm run node
```

**Terminal 2 - Deploy:**
```bash
npm run deploy
```

**Expected output:**
```
🚀 Deploying TournamentRegistry to Avalanche Fuji...
📡 Network: localhost
⛓️  Chain ID: 31337
👤 Deploying with account: 0x...
💰 Account balance: 10000.0 AVAX
✅ TournamentRegistry deployed to: 0x5FbDB2315678afecb367f032d93F642f64180aa3
📝 Contract info saved to: contract-address.json
```

### 3. Deploy on Avalanche Fuji Testnet

**Prerequisites:**
1. Have AVAX on Fuji testnet ([Faucet](https://faucet.avax.network/))
2. Configure `PRIVATE_KEY` in `.env`

**Command:**
```bash
npx hardhat run scripts/deploy.js --network fuji
```

**Verify on Snowtrace:**
```
https://testnet.snowtrace.io/address/<CONTRACT_ADDRESS>
```

### 4. Interact with the Contract (Console)

```bash
npx hardhat console --network localhost
```

```javascript
const TournamentRegistry = await ethers.getContractFactory("TournamentRegistry");
const registry = await TournamentRegistry.attach("0x5FbDB2...");

// Register tournament
const tx = await registry.registerTournament(
  "Summer Tournament 2025",
  ["0xAddress1", "0xAddress2"],
  ["Player1", "Player2"]
);
await tx.wait();

// Read record
const record = await registry.getTournament(0);
console.log(record);
```

## 📄 Generated Files

### contract-address.json

Automatically generated after deployment:

```json
{
  "contractAddress": "0x5FbDB2315678afecb367f032d93F642f64180aa3",
  "network": "fuji",
  "chainId": 43113,
  "deployedAt": "2025-12-05T10:30:00.000Z",
  "deployer": "0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb"
}
```

This file is used by:
- `backend/blockchain/blockchain-service.js` - To connect to the contract
- `frontend/src/services/blockchainService.ts` - To display info

## 🧪 Testing (Optional)

Create `test/TournamentRegistry.test.js`:

```javascript
const { expect } = require("chai");
const { ethers } = require("hardhat");

describe("TournamentRegistry", function () {
  it("Should register a tournament", async function () {
    const TournamentRegistry = await ethers.getContractFactory("TournamentRegistry");
    const registry = await TournamentRegistry.deploy();
    
    await registry.registerTournament(
      "Test Tournament",
      [await ethers.getSigner(0).getAddress()],
      ["TestPlayer"]
    );
    
    const record = await registry.getTournament(0);
    expect(record.tournamentName).to.equal("Test Tournament");
  });
});
```

**Run:**
```bash
npm run test
```

## 🌐 Supported Networks

| Network | Chain ID | RPC URL | Explorer |
|---------|----------|---------|----------|
| **Hardhat** | 31337 | http://127.0.0.1:8545 | N/A |
| **Localhost** | 31337 | http://127.0.0.1:8545 | N/A |
| **Avalanche Fuji** | 43113 | https://api.avax-test.network/ext/bc/C/rpc | [Snowtrace Testnet](https://testnet.snowtrace.io) |

## 🔍 Troubleshooting

### Error: "Account has no AVAX"

**Solution:**
- Get test AVAX from [Fuji Faucet](https://faucet.avax.network/)
- Verify that `PRIVATE_KEY` in `.env` is correct

### Error: "Cannot find module 'hardhat'"

**Solution:**
```bash
npm install
```

### Error: "Invalid private key"

**Solution:**
- Verify format: must start with `0x` and have 66 characters
- Verify that `.env` is located at `/srcs/secrets/.env`

### Slow Compilation

**Solution:**
```bash
npm run clean  # Clears cache
npm run compile
```

## 📚 Related Documentation

- [TournamentRegistry Smart Contract](./contracts/README.md) - Solidity contract documentation
- [Deployment Scripts](./scripts/README.md) - deploy.js documentation
- [Blockchain Service](../README.md) - Blockchain backend service

## 🔗 Useful Links

- [Hardhat Docs](https://hardhat.org/docs)
- [Avalanche Docs](https://docs.avax.network/)
- [Snowtrace (Explorer)](https://snowtrace.io/)
- [Fuji Faucet](https://faucet.avax.network/)
- [ethers.js v6 Docs](https://docs.ethers.org/v6/)

---

**⚡ Hardhat Project** - TournamentRegistry Smart Contract  
*Last updated: December 2025*