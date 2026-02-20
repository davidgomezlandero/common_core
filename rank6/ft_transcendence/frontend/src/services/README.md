# 🔌 Services - Frontend Services Layer

## 📋 General Overview

This directory contains the **services layer** of the frontend, which abstracts all communication with the backend and external services. It provides typed TypeScript interfaces to consume REST APIs, WebSockets and blockchain services.

## 📄 Main File

```
services/
└── blockchainService.ts    # Blockchain communication service (62 lines)
```

## 🎯 Services Architecture

### Design Pattern

Services follow the **Service Layer** pattern:

```
Frontend Components
       ↓
   Services Layer  ← (WE ARE HERE)
       ↓
   Backend API
       ↓
   Database / Blockchain
```

**Advantages:**
- ✅ **Separation of Concerns** - Business logic separated from UI
- ✅ **Reusability** - Same services used by multiple components
- ✅ **Testability** - Easy to mock in tests
- ✅ **TypeScript Typing** - Interfaces for requests/responses
- ✅ **Maintainability** - API changes centralized

## 📦 blockchainService.ts

### Purpose

Provides methods to interact with the **blockchain module** of the backend, querying tournament information registered on the Avalanche blockchain.

### TypeScript Interfaces

```typescript
export interface Tournament {
    recordId: string;           // Blockchain record ID
    tournamentName: string;     // Tournament name
    players: string[];          // Ethereum addresses of players
    aliases: string[];          // Player nicknames
    champion: string;           // Winner address
    scores: string[];           // Final scores
    timestamp: string;          // Registration timestamp
    isFinalized: boolean;       // true = tournament completed
}

export interface PlayerStats {
    totalTournaments: string;   // Tournaments played
    tournamentsWon: string;     // Tournaments won
    totalScore: string;         // Total accumulated score
}

export interface BlockchainStatus {
    status: string;             // "connected" | "disconnected"
    network: string;            // "fuji" | "localhost"
    contractAddress: string;    // Smart contract address
    wallet: string;             // Backend wallet address
    snowtraceUrl: string;       // URL to blockchain explorer
}
```

### Available Methods

#### 1. `getStatus()`

**Purpose:** Gets the blockchain connection status.

```typescript
async getStatus(): Promise<BlockchainStatus>
```

**Usage:**
```typescript
import { blockchainService } from '@/services/blockchainService';

const status = await blockchainService.getStatus();
console.log(`Connected to ${status.network}`);
console.log(`Contract: ${status.contractAddress}`);
```

**Backend Endpoint:**
```
GET /api/blockchain/status
```

**Example Response:**
```json
{
  "status": "connected",
  "network": "fuji",
  "contractAddress": "0x8A791620dd6260079BF849Dc5567aDC3F2FdC318",
  "wallet": "0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb",
  "snowtraceUrl": "https://testnet.snowtrace.io/address/0x8A791620..."
}
```

#### 2. `getAllTournaments()`

**Purpose:** Gets all tournaments registered on the blockchain.

```typescript
async getAllTournaments(): Promise<Tournament[]>
```

**Usage:**
```typescript
const tournaments = await blockchainService.getAllTournaments();
console.log(`Total tournaments: ${tournaments.length}`);

tournaments.forEach(t => {
  console.log(`${t.tournamentName}: ${t.isFinalized ? 'Finished' : 'In Progress'}`);
});
```

**Backend Endpoint:**
```
GET /api/blockchain/tournaments
```

**Example Response:**
```json
{
  "tournaments": [
    {
      "recordId": "0",
      "tournamentName": "Summer Cup 2025",
      "players": ["0x742d...", "0x8626..."],
      "aliases": ["Alice", "Bob"],
      "champion": "0x742d...",
      "scores": ["100", "75"],
      "timestamp": "2025-06-15T10:00:00Z",
      "isFinalized": true
    }
  ]
}
```

#### 3. `getTournament(id)`

**Purpose:** Gets information about a specific tournament.

```typescript
async getTournament(id: string): Promise<Tournament>
```

**Parameters:**
- `id` - Blockchain record ID (string)

**Usage:**
```typescript
const tournament = await blockchainService.getTournament("0");
console.log(`Winner: ${tournament.champion}`);
console.log(`Scores: ${tournament.scores.join(', ')}`);
```

**Backend Endpoint:**
```
GET /api/blockchain/tournaments/:id
```

#### 4. `getPlayerStats(alias)`

**Purpose:** Gets aggregated statistics for a player.

```typescript
async getPlayerStats(alias: string): Promise<PlayerStats>
```

**Parameters:**
- `alias` - Player nickname

**Usage:**
```typescript
const stats = await blockchainService.getPlayerStats("Alice");
console.log(`Tournaments played: ${stats.totalTournaments}`);
console.log(`Tournaments won: ${stats.tournamentsWon}`);
console.log(`Total score: ${stats.totalScore}`);

const winRate = (parseInt(stats.tournamentsWon) / parseInt(stats.totalTournaments)) * 100;
console.log(`Win rate: ${winRate.toFixed(1)}%`);
```

**Backend Endpoint:**
```
GET /api/blockchain/player/:alias/stats
```

**Example Response:**
```json
{
  "totalTournaments": "5",
  "tournamentsWon": "3",
  "totalScore": "450"
}
```

### Error Handling

All methods throw exceptions on error:

```typescript
try {
  const tournaments = await blockchainService.getAllTournaments();
  // Process tournaments...
} catch (error) {
  console.error('Failed to fetch tournaments:', error);
  // Show error message to user
}
```

**Common Errors:**
- `Failed to fetch blockchain status` - Backend unavailable
- `Failed to fetch tournaments` - Blockchain disconnected
- `Failed to fetch player stats` - Player not found

## 🔄 Component Integration

### Example: Tournaments Component

```typescript
// Components/Tournaments.tsx
import React, { useEffect, useState } from 'react';
import { blockchainService, Tournament } from '@/services/blockchainService';

export const Tournaments: React.FC = () => {
  const [tournaments, setTournaments] = useState<Tournament[]>([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    const loadTournaments = async () => {
      try {
        const data = await blockchainService.getAllTournaments();
        setTournaments(data);
      } catch (err) {
        setError('Failed to load tournaments');
        console.error(err);
      } finally {
        setLoading(false);
      }
    };

    loadTournaments();
  }, []);

  if (loading) return <div>Loading...</div>;
  if (error) return <div>Error: {error}</div>;

  return (
    <div>
      <h2>Blockchain Tournaments</h2>
      {tournaments.map(t => (
        <div key={t.recordId}>
          <h3>{t.tournamentName}</h3>
          <p>Status: {t.isFinalized ? '✅ Finished' : '⏳ In Progress'}</p>
          {t.isFinalized && <p>Champion: {t.champion}</p>}
        </div>
      ))}
    </div>
  );
};
```

## 🚀 Future Services (Expandable)

This directory can grow with more services:

```
services/
├── blockchainService.ts     # Current
├── authService.ts           # Authentication and sessions
├── chatService.ts           # WebSocket chat
├── gameService.ts           # WebSocket game
├── userService.ts           # User CRUD
├── tournamentService.ts     # Tournament CRUD (DB)
├── matchService.ts          # Matchmaking
├── profileService.ts        # Profiles and statistics
├── friendService.ts         # Friends system
└── uploadService.ts         # Avatar upload
```

### Template for New Services

```typescript
// services/exampleService.ts

const API_URL = `${window.location.origin}/api/example`;

export interface ExampleData {
    id: string;
    name: string;
}

export const exampleService = {
    async getAll(): Promise<ExampleData[]> {
        const response = await fetch(`${API_URL}`, {
            headers: { 'Accept': 'application/json' }
        });
        if (!response.ok) {
            throw new Error('Failed to fetch data');
        }
        return response.json();
    },

    async getById(id: string): Promise<ExampleData> {
        const response = await fetch(`${API_URL}/${id}`, {
            headers: { 'Accept': 'application/json' }
        });
        if (!response.ok) {
            throw new Error('Failed to fetch data');
        }
        return response.json();
    },

    async create(data: Omit<ExampleData, 'id'>): Promise<ExampleData> {
        const response = await fetch(`${API_URL}`, {
            method: 'POST',
            headers: { 
                'Content-Type': 'application/json',
                'Accept': 'application/json'
            },
            body: JSON.stringify(data)
        });
        if (!response.ok) {
            throw new Error('Failed to create data');
        }
        return response.json();
    }
};
```

## 📝 Code Conventions

### Naming Conventions

- ✅ Files: `camelCase.ts` (e.g.: `blockchainService.ts`)
- ✅ Interfaces: `PascalCase` (e.g.: `Tournament`, `PlayerStats`)
- ✅ Exported services: `camelCase` (e.g.: `blockchainService`)
- ✅ Methods: `camelCase` (e.g.: `getAllTournaments`)

### TypeScript Best Practices

```typescript
// ✅ GOOD: Exported interfaces
export interface Tournament { ... }

// ✅ GOOD: Async/await with typed Promise
async getStatus(): Promise<BlockchainStatus> { ... }

// ✅ GOOD: Explicit headers
headers: { 'Accept': 'application/json' }

// ❌ BAD: Any types
async getData(): Promise<any> { ... }

// ❌ BAD: Without error handling
const data = await fetch(url).then(r => r.json());
```

### HTTP Headers

Always include appropriate headers:

```typescript
// GET requests
headers: { 'Accept': 'application/json' }

// POST/PUT requests
headers: { 
    'Content-Type': 'application/json',
    'Accept': 'application/json'
}

// With authentication (if applicable)
headers: { 
    'Accept': 'application/json',
    'Authorization': `Bearer ${token}`
}
```

## 🧪 Testing

### Unit Tests (Example)

```typescript
// services/__tests__/blockchainService.test.ts
import { blockchainService } from '../blockchainService';

// Mock fetch
global.fetch = jest.fn();

describe('blockchainService', () => {
  beforeEach(() => {
    (fetch as jest.Mock).mockClear();
  });

  it('should fetch blockchain status', async () => {
    (fetch as jest.Mock).mockResolvedValueOnce({
      ok: true,
      json: async () => ({
        status: 'connected',
        network: 'fuji'
      })
    });

    const status = await blockchainService.getStatus();
    expect(status.network).toBe('fuji');
  });

  it('should handle errors', async () => {
    (fetch as jest.Mock).mockResolvedValueOnce({
      ok: false
    });

    await expect(blockchainService.getStatus()).rejects.toThrow();
  });
});
```

## 📚 Related Documentation

- [Frontend README](../../README.md) - General frontend documentation
- [Backend API](../../../backend/README.md) - Backend endpoints
- [Blockchain Service](../../../backend/blockchain/README.md) - Backend blockchain service
- [Components](../Components/README.md) - Components that use these services

## 🔗 Useful Links

- [Fetch API](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API)
- [TypeScript Handbook](https://www.typescriptlang.org/docs/handbook/intro.html)
- [React Query](https://tanstack.com/query/latest) - Recommended library for data fetching
- [Axios](https://axios-http.com/) - Alternative to fetch with more features

---

**🔌 Services Layer** - Frontend API Communication  
*Last updated: December 2025*
