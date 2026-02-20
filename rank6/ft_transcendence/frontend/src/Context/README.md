# 🧠 Context - React Contexts for Global State

## 📋 General Overview

This directory contains the **React Contexts** that manage the **global state** of the application. Using React's Context API, these modules provide shared data and functions across multiple components without the need for prop drilling.

## 🗂️ Context Structure

### 🔐 `AuthContext.tsx` - Authentication Context

**Purpose**: Manage the user authentication state throughout the application.

#### 📦 Provided State

```typescript
interface AuthContextType {
  user: User | null;              // Authenticated user (null if not logged in)
  token: string | null;           // JWT token for authentication
  isAuthenticated: boolean;       // Convenience boolean
  login: (credentials: LoginCredentials) => Promise<void>;
  logout: () => void;
  register: (userData: RegisterData) => Promise<void>;
  updateProfile: (updates: Partial<User>) => Promise<void>;
  loading: boolean;               // Loading token verification
}

interface User {
  id: number;
  username: string;
  email: string;
  displayName: string;
  avatar?: string;
  stats: {
    wins: number;
    losses: number;
    winRate: number;
    elo: number;
  };
  createdAt: string;
}
```

#### 🔄 Lifecycle

```
1. App.tsx → <AuthProvider> wrap
2. On mount → verifyToken() with localStorage
3. If valid token → fetch user data
4. setUser(userData) → isAuthenticated = true
5. Child components can use useAuth()
```

#### 🔌 Implementation

```typescript
// AuthContext.tsx
import { createContext, useContext, useState, useEffect } from 'react';

const AuthContext = createContext<AuthContextType | undefined>(undefined);

export function AuthProvider({ children }: { children: React.ReactNode }) {
  const [user, setUser] = useState<User | null>(null);
  const [token, setToken] = useState<string | null>(
    localStorage.getItem('auth_token')
  );
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    if (token) {
      verifyAndFetchUser(token);
    } else {
      setLoading(false);
    }
  }, [token]);

  const verifyAndFetchUser = async (token: string) => {
    try {
      const response = await fetch('/api/auth/verify', {
        headers: { Authorization: `Bearer ${token}` }
      });
      if (response.ok) {
        const userData = await response.json();
        setUser(userData);
      } else {
        // Invalid or expired token
        localStorage.removeItem('auth_token');
        setToken(null);
      }
    } catch (error) {
      console.error('Error verifying token:', error);
    } finally {
      setLoading(false);
    }
  };

  const login = async (credentials: LoginCredentials) => {
    const response = await fetch('/api/auth/login', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(credentials)
    });
    
    if (!response.ok) throw new Error('Login failed');
    
    const { token, user } = await response.json();
    localStorage.setItem('auth_token', token);
    setToken(token);
    setUser(user);
  };

  const logout = () => {
    localStorage.removeItem('auth_token');
    setToken(null);
    setUser(null);
    // Optional: call /api/auth/logout to invalidate token in backend
  };

  return (
    <AuthContext.Provider 
      value={{ 
        user, 
        token, 
        isAuthenticated: !!user, 
        login, 
        logout, 
        loading 
      }}
    >
      {children}
    </AuthContext.Provider>
  );
}

export function useAuth() {
  const context = useContext(AuthContext);
  if (!context) {
    throw new Error('useAuth must be used within AuthProvider');
  }
  return context;
}
```

#### 🎯 Usage in Components

```typescript
// Login.tsx
import { useAuth } from '../Context/AuthContext';

function Login() {
  const { login, isAuthenticated } = useAuth();
  const navigate = useNavigate();

  const handleSubmit = async (e: FormEvent) => {
    e.preventDefault();
    try {
      await login({ username, password });
      navigate('/index');
    } catch (error) {
      setError('Invalid credentials');
    }
  };

  if (isAuthenticated) {
    return <Navigate to="/index" />;
  }

  return <form onSubmit={handleSubmit}>...</form>;
}
```

#### 🔒 Security

- **Token Storage**: localStorage (consider httpOnly cookies for better security)
- **Token Expiration**: Backend must include `exp` claim in JWT
- **Refresh Tokens**: Implement `/api/auth/refresh` endpoint to renew without re-login
- **HTTPS Only**: Never transmit tokens over unencrypted HTTP

---

### 🧩 `ComponentsContext.tsx` - Global Components Context

**Purpose**: Manage shared state between components (socket, notifications, modals).

#### 📦 Provided State

```typescript
interface ComponentsContextType {
  socket: Socket | null;                    // Socket.IO instance
  notifications: Notification[];            // Notification queue
  activeModal: string | null;               // Currently open modal
  rooms: Room[];                            // Available game rooms
  onlineUsers: number[];                    // Online user IDs
  
  // Methods
  initSocket: () => void;
  disconnectSocket: () => void;
  addNotification: (notif: Notification) => void;
  clearNotifications: () => void;
  openModal: (modalId: string) => void;
  closeModal: () => void;
  refreshRooms: () => Promise<void>;
}

interface Room {
  id: string;
  name: string;
  host: User;
  players: number;
  maxPlayers: number;
  mode: 'AI' | 'PvP' | 'Tournament';
  status: 'waiting' | 'playing' | 'finished';
}

interface Notification {
  id: string;
  type: 'info' | 'success' | 'warning' | 'error';
  title: string;
  message: string;
  timestamp: number;
  duration?: number;  // Auto-dismiss after X ms
}
```

#### 🔌 Socket.IO Integration

```typescript
// ComponentsContext.tsx
import { io, Socket } from 'socket.io-client';

export function ComponentsProvider({ children }: { children: React.ReactNode }) {
  const [socket, setSocket] = useState<Socket | null>(null);
  const { token, isAuthenticated } = useAuth();

  const initSocket = useCallback(() => {
    if (!token || socket) return;

    const newSocket = io('http://localhost:3000', {
      auth: { token },
      transports: ['websocket', 'polling']
    });

    newSocket.on('connect', () => {
      console.log('Socket connected:', newSocket.id);
      addNotification({
        id: Date.now().toString(),
        type: 'success',
        title: 'Connected',
        message: 'Connection established with the server',
        timestamp: Date.now(),
        duration: 3000
      });
    });

    newSocket.on('disconnect', () => {
      console.log('Socket disconnected');
    });

    newSocket.on('notification', (data: Notification) => {
      addNotification(data);
    });

    newSocket.on('user-online', (userId: number) => {
      setOnlineUsers(prev => [...prev, userId]);
    });

    newSocket.on('user-offline', (userId: number) => {
      setOnlineUsers(prev => prev.filter(id => id !== userId));
    });

    setSocket(newSocket);
  }, [token, socket]);

  useEffect(() => {
    if (isAuthenticated && !socket) {
      initSocket();
    }
    return () => {
      if (socket) {
        socket.disconnect();
      }
    };
  }, [isAuthenticated]);

  return (
    <ComponentsContext.Provider value={{ socket, ... }}>
      {children}
    </ComponentsContext.Provider>
  );
}
```

#### 🎨 Notification System

```typescript
// Usage in any component
const { addNotification } = useComponents();

// Success notification
addNotification({
  id: crypto.randomUUID(),
  type: 'success',
  title: 'Match created',
  message: 'The game room has been successfully created',
  timestamp: Date.now(),
  duration: 5000  // Auto-dismiss in 5 seconds
});

// Persistent error notification
addNotification({
  id: crypto.randomUUID(),
  type: 'error',
  title: 'Connection error',
  message: 'Could not connect to the server',
  timestamp: Date.now()
  // No duration → persists until user closes it
});
```

#### 🔔 Notification Component

```typescript
// NotificationToast.tsx
function NotificationToast() {
  const { notifications, clearNotifications } = useComponents();

  useEffect(() => {
    // Auto-dismiss notifications with duration
    notifications.forEach(notif => {
      if (notif.duration) {
        setTimeout(() => {
          removeNotification(notif.id);
        }, notif.duration);
      }
    });
  }, [notifications]);

  return (
    <div className="fixed top-4 right-4 z-50 space-y-2">
      {notifications.map(notif => (
        <div 
          key={notif.id}
          className={`p-4 rounded shadow-lg ${getColorClass(notif.type)}`}
        >
          <h4 className="font-bold">{notif.title}</h4>
          <p>{notif.message}</p>
        </div>
      ))}
    </div>
  );
}
```

---

### 🏆 `TournamentContext.jsx` - Tournament Context

**Purpose**: Manage the state of elimination tournaments (bracket, rounds, progress).

#### 📦 Provided State

```javascript
interface TournamentContextType {
  currentTournament: Tournament | null;
  bracket: BracketNode[];
  currentRound: number;
  totalRounds: number;
  isActive: boolean;
  
  createTournament: (players: Player[]) => void;
  startTournament: () => void;
  advanceMatch: (matchId: string, winnerId: number) => void;
  resetTournament: () => void;
  getTournamentWinner: () => Player | null;
}

interface Tournament {
  id: string;
  name: string;
  players: Player[];
  status: 'setup' | 'active' | 'finished';
  createdAt: number;
}

interface BracketNode {
  matchId: string;
  round: number;
  position: number;
  player1: Player | null;
  player2: Player | null;
  winner: Player | null;
  nextMatchId: string | null;  // Match the winner advances to
}
```

#### 🏗️ Bracket Generation

```javascript
// TournamentContext.jsx
function generateBracket(players) {
  // Validate it is a power of 2
  if (!isPowerOfTwo(players.length)) {
    throw new Error('The number of players must be a power of 2');
  }

  const rounds = Math.log2(players.length);
  const bracket = [];

  // First round: match players
  for (let i = 0; i < players.length; i += 2) {
    bracket.push({
      matchId: `round1-match${i/2}`,
      round: 1,
      position: i / 2,
      player1: players[i],
      player2: players[i + 1],
      winner: null,
      nextMatchId: `round2-match${Math.floor(i/4)}`
    });
  }

  // Subsequent rounds: empty matches
  for (let r = 2; r <= rounds; r++) {
    const matchesInRound = Math.pow(2, rounds - r);
    for (let m = 0; m < matchesInRound; m++) {
      bracket.push({
        matchId: `round${r}-match${m}`,
        round: r,
        position: m,
        player1: null,
        player2: null,
        winner: null,
        nextMatchId: r < rounds ? `round${r+1}-match${Math.floor(m/2)}` : null
      });
    }
  }

  return bracket;
}
```

#### 🎮 Tournament Flow

```javascript
// Create tournament
const { createTournament, startTournament } = useTournament();

const players = [
  { id: 1, username: 'Alice' },
  { id: 2, username: 'Bob' },
  { id: 3, username: 'Charlie' },
  { id: 4, username: 'David' }
];

createTournament(players);  // Generates 2-round bracket

// Start first round
startTournament();  // status: 'setup' → 'active'

// When a match ends
advanceMatch('round1-match0', 1);  // Alice wins
// → Alice advances to round2-match0.player1

advanceMatch('round1-match1', 3);  // Charlie wins
// → Charlie advances to round2-match0.player2

// Semifinal
advanceMatch('round2-match0', 1);  // Alice wins
// → Alice is tournament champion
// → status: 'active' → 'finished'
```

#### 🎨 Bracket Visualization

```jsx
// Tournamenst.jsx
function TournamentBracket() {
  const { bracket, currentRound } = useTournament();

  const groupedByRound = bracket.reduce((acc, match) => {
    if (!acc[match.round]) acc[match.round] = [];
    acc[match.round].push(match);
    return acc;
  }, {});

  return (
    <div className="flex gap-8">
      {Object.entries(groupedByRound).map(([round, matches]) => (
        <div key={round} className="flex flex-col gap-4">
          <h3>Round {round}</h3>
          {matches.map(match => (
            <MatchCard 
              key={match.matchId} 
              match={match}
              isActive={match.round === currentRound}
            />
          ))}
        </div>
      ))}
    </div>
  );
}
```

#### 🏅 Victory Confetti

```javascript
// When final winner is detected
useEffect(() => {
  const winner = getTournamentWinner();
  if (winner) {
    setShowConfetti(true);
    addNotification({
      type: 'success',
      title: 'Tournament Completed!',
      message: `${winner.username} is the champion`
    });
  }
}, [currentTournament?.status]);
```

---

## 🔗 Context Integration

### Dependencies

```
TournamentContext → uses useAuth() to validate permissions
ComponentsContext → uses useAuth() to initialize socket
AuthContext → independent (base)
```

### Composition in App.tsx

```typescript
function App() {
  return (
    <AuthProvider>
      <ComponentsProvider>
        <TournamentProvider>
          <RouterProvider router={router} />
        </TournamentProvider>
      </ComponentsProvider>
    </AuthProvider>
  );
}
```

## 🛠️ Custom Hooks

Each context exports a custom hook:

```typescript
// AuthContext.tsx
export function useAuth() { ... }

// ComponentsContext.tsx
export function useComponents() { ... }

// TournamentContext.jsx
export function useTournament() { ... }
```

**Advantage**: Automatic validation of usage within Provider.

## 🧪 Context Testing

```typescript
// AuthContext.test.tsx
import { renderHook, act } from '@testing-library/react';

describe('AuthContext', () => {
  it('should login user successfully', async () => {
    const { result } = renderHook(() => useAuth(), {
      wrapper: AuthProvider
    });

    await act(async () => {
      await result.current.login({
        username: 'testuser',
        password: 'password123'
      });
    });

    expect(result.current.isAuthenticated).toBe(true);
    expect(result.current.user).toBeDefined();
  });
});
```

## 📊 Data Flow

```
Backend API/Socket
    ↓
Context Providers (global state)
    ↓
useAuth() / useComponents() / useTournament() (hooks)
    ↓
React Components (UI)
```

## 🚀 Future Improvements

- [ ] **Persistence**: Save tournament state in localStorage
- [ ] **Optimization**: Use `useReducer` instead of multiple `useState`
- [ ] **DevTools**: Integrate Redux DevTools for debugging
- [ ] **TypeScript**: Migrate `TournamentContext.jsx` to `.tsx`
- [ ] **Testing**: Increase coverage to 80%+

---

**Location**: `/frontend/src/Context/`  
**Technologies**: React Context API, Socket.IO Client, TypeScript  
**Related documentation**:
- `../Components/README.md` - Components that consume contexts
- `../types.tsx` - Shared TypeScript interfaces
- `/backend/pon-server.js` - Server Socket.IO events