# 🚀 Deployment Scripts - Blockchain Deployment

## 📋 General Description

This directory contains the **deployment scripts** for the `TournamentRegistry` smart contract on Avalanche-compatible blockchain networks.

## 📄 Main File

```
scripts/
└── deploy.js    # Main deployment script (56 lines)
```

## 🎯 Purpose

The `deploy.js` script automates the complete contract deployment process:

1. ✅ Validates network and wallet configuration
2. ✅ Verifies sufficient AVAX balance
3. ✅ Deploys the `TournamentRegistry` contract
4. ✅ Waits for blockchain confirmation
5. ✅ Saves deployment information to `contract-address.json`
6. ✅ Displays link to blockchain explorer

## 🔧 Script Usage

### Deploy on Localhost (Development)

**Terminal 1 - Start local node:**
```bash
cd backend/blockchain/hardhat
npm run node
```

**Terminal 2 - Deploy:**
```bash
npm run deploy
# Equivalent to: hardhat run scripts/deploy.js --network localhost
```

### Deploy on Avalanche Fuji (Testnet)

**Prerequisites:**
1. Configure `PRIVATE_KEY` in `/srcs/secrets/.env`
2. Have test AVAX (get it at [Faucet](https://faucet.avax.network/))

**Command:**
```bash
npx hardhat run scripts/deploy.js --network fuji
```

### Deploy on Hardhat Network (Ephemeral Testing)

```bash
npm run deploy:hardhat
# Ephemeral testing network, destroyed after execution
```

## 📊 Script Output

### Successful Execution Example

```bash
$ npm run deploy

🚀 Deploying TournamentRegistry to Avalanche Fuji...
📡 Network: fuji
⛓️  Chain ID: 43113
👤 Deploying with account: 0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb
💰 Account balance: 2.5 AVAX

📦 Deploying contract...

✅ TournamentRegistry deployed to: 0x8A791620dd6260079BF849Dc5567aDC3F2FdC318
📝 Contract info saved to: /backend/blockchain/hardhat/contract-address.json

🔍 View on Snowtrace:
   https://testnet.snowtrace.io/address/0x8A791620dd6260079BF849Dc5567aDC3F2FdC318

⏳ Wait ~30 seconds for contract to be indexed...

🎉 Deployment completed successfully!

💰 Remaining balance: 2.3 AVAX
```

### Error Example (No AVAX)

```bash
🚀 Deploying TournamentRegistry to Avalanche Fuji...
📡 Network: fuji
⛓️  Chain ID: 43113
👤 Deploying with account: 0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb
💰 Account balance: 0 AVAX

❌ ERROR: Account has no AVAX
```

## 📄 Generated File: contract-address.json

The script automatically saves the deployment information:

**Location:** `backend/blockchain/hardhat/contract-address.json`

**Structure:**
```json
{
  "contractAddress": "0x8A791620dd6260079BF849Dc5567aDC3F2FdC318",
  "network": "fuji",
  "chainId": 43113,
  "deployedAt": "2025-12-05T10:30:45.123Z",
  "deployer": "0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb"
}
```

### File Usage

This JSON is consumed by:

1. **Backend (`blockchain-service.js`)**
   ```javascript
   const contractInfo = JSON.parse(fs.readFileSync('./contract-address.json'));
   const contractAddress = contractInfo.contractAddress;
   ```

2. **Frontend (`blockchainService.ts`)**
   - Displays contract address in UI
   - Generates links to Snowtrace

## 🔍 Script Anatomy

### 1. Imports

```javascript
const hre = require("hardhat");        // Hardhat Runtime Environment
const fs = require('fs');              // File system for saving JSON
const path = require('path');          // Path utilities
```

### 2. Configuration Retrieval

```javascript
const [deployer] = await hre.ethers.getSigners();
console.log("👤 Deploying with account:", deployer.address);

const balance = await hre.ethers.provider.getBalance(deployer.address);
console.log("💰 Account balance:", hre.ethers.formatEther(balance), "AVAX");
```

### 3. Balance Validation

```javascript
if (balance === 0n) {
  console.error("❌ ERROR: Account has no AVAX");
  process.exit(1);
}
```

**Important:** The script verifies that there are funds **before** attempting to deploy.

### 4. Contract Deployment

```javascript
const TournamentRegistry = await hre.ethers.getContractFactory("TournamentRegistry");
const registry = await TournamentRegistry.deploy();

await registry.waitForDeployment();  // Waits for blockchain confirmation
const address = await registry.getAddress();
```

**ethers.js v6:** Uses `waitForDeployment()` and `getAddress()` (v5 used `deployed()` and `.address`)

### 5. Information Saving

```javascript
const deployInfo = {
  contractAddress: address,
  network: hre.network.name,
  chainId: hre.network.config.chainId,
  deployedAt: new Date().toISOString(),
  deployer: deployer.address
};

const outputPath = path.join(__dirname, '..', 'contract-address.json');
fs.writeFileSync(outputPath, JSON.stringify(deployInfo, null, 2));
```

### 6. Useful Links

```javascript
console.log("🔍 View on Snowtrace:");
console.log(`   https://testnet.snowtrace.io/address/${address}`);
```

## 🌐 Available Networks

| Network | Network Flag | Chain ID | RPC URL |
|---------|--------------|----------|---------|
| **Localhost** | `--network localhost` | 31337 | http://127.0.0.1:8545 |
| **Hardhat** | `--network hardhat` | 31337 | In-memory |
| **Fuji** | `--network fuji` | 43113 | https://api.avax-test.network/ext/bc/C/rpc |

### Configuration in hardhat.config.js

```javascript
networks: {
  localhost: {
    url: "http://127.0.0.1:8545"
  },
  fuji: {
    url: process.env.AVALANCHE_RPC_URL || "https://api.avax-test.network/ext/bc/C/rpc",
    chainId: 43113,
    accounts: [process.env.PRIVATE_KEY]
  }
}
```

## 💰 Deployment Costs

### Estimated Gas

| Network | Gas Cost | Cost in AVAX | Cost in USD* |
|---------|----------|--------------|--------------|
| **Localhost** | ~1,500,000 | 0 (free) | $0 |
| **Hardhat** | ~1,500,000 | 0 (free) | $0 |
| **Fuji Testnet** | ~1,500,000 | ~0.00015 | $0 (testnet) |

*Approximate values. Fuji uses test AVAX with no real value.

### Getting Test AVAX

**Avalanche Fuji Faucet:**
- URL: https://faucet.avax.network/
- Amount: 2 AVAX (sufficient for ~10 deployments)
- Cooldown: 24 hours

**Steps:**
1. Go to https://faucet.avax.network/
2. Select "C-Chain"
3. Paste your wallet address
4. Complete CAPTCHA
5. Wait ~10 seconds

## 🔧 Troubleshooting

### Error: "Cannot find module 'hardhat'"

**Cause:** Dependencies not installed.

**Solution:**
```bash
npm install
```

### Error: "Invalid private key"

**Cause:** `PRIVATE_KEY` misconfigured in `.env`

**Solution:**
```bash
# Verify the file exists
cat /sgoinfre/students/sternero/transcendence/srcs/secrets/.env

# Correct format:
PRIVATE_KEY=0x123456789abcdef...  # Must start with 0x and have 66 characters
```

### Error: "Account has no AVAX"

**Cause:** Wallet without funds.

**Solution:**
1. Get AVAX from [Fuji Faucet](https://faucet.avax.network/)
2. Verify balance:
   ```javascript
   npx hardhat console --network fuji
   > const balance = await ethers.provider.getBalance("0xYOUR_ADDRESS");
   > ethers.formatEther(balance)
   ```

### Error: "Network fuji not found"

**Cause:** Incorrect network configuration.

**Solution:**
```bash
# Check hardhat.config.js
cat hardhat.config.js | grep -A 5 "fuji:"
```

### Slow Deployment

**Cause:** Congested network or slow RPC.

**Solution:**
- Use an alternative RPC in `hardhat.config.js`
- Increase timeout in configuration

## 🧪 Deployment Verification

### Verify on Blockchain Explorer

```bash
# URL automatically generated by the script
https://testnet.snowtrace.io/address/<CONTRACT_ADDRESS>
```

### Verify from Code

```javascript
// Hardhat console
npx hardhat console --network fuji

// Load contract
const address = require('./contract-address.json').contractAddress;
const TournamentRegistry = await ethers.getContractFactory("TournamentRegistry");
const registry = TournamentRegistry.attach(address);

// Verify functionality
const count = await registry.getTournamentCount();
console.log("Tournament count:", count.toString());
```

## 📚 Additional Scripts (Optional)

You can create additional scripts in this directory:

### `verify.js` - Verify Contract on Snowtrace

```javascript
const hre = require("hardhat");

async function main() {
  const address = require('../contract-address.json').contractAddress;
  
  await hre.run("verify:verify", {
    address: address,
    constructorArguments: []
  });
}

main().catch((error) => {
  console.error(error);
  process.exit(1);
});
```

### `interact.js` - Interact with Contract

```javascript
const hre = require("hardhat");

async function main() {
  const address = require('../contract-address.json').contractAddress;
  const TournamentRegistry = await hre.ethers.getContractFactory("TournamentRegistry");
  const registry = TournamentRegistry.attach(address);
  
  // Register test tournament
  const tx = await registry.registerTournament(
    "Test Tournament",
    [await hre.ethers.getSigner(0).getAddress()],
    ["TestPlayer"]
  );
  await tx.wait();
  
  console.log("Tournament registered!");
}

main();
```

## 📚 Related Documentation

- [Hardhat Project](../README.md) - Environment configuration
- [Smart Contract](../contracts/README.md) - Contract documentation
- [Blockchain Service](../../README.md) - Backend integration

## 🔗 Useful Links

- [Hardhat Deploy Plugin](https://github.com/wighawag/hardhat-deploy)
- [ethers.js Contract Deployment](https://docs.ethers.org/v6/getting-started/#starting-contracts)
- [Avalanche Deploy Guide](https://docs.avax.network/build/dapp/smart-contracts/deploy-a-smart-contract)
- [Snowtrace API](https://docs.snowtrace.io/)

---

**🚀 Deployment Scripts** - TournamentRegistry Automation  
*Last updated: December 2025*