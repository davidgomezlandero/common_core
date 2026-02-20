# 📂 Frontend/src - React Application Source Code

## 📋 General Overview

This directory contains the **complete source code** of the SPA (Single Page Application) developed in React 19 + TypeScript. It includes components, contexts, middleware, types and application entry points.

## 🗂️ File Structure

```
src/
├── main.tsx              # Application entry point
├── App.tsx               # Root component with routing
├── App.css               # App component styles
├── index.css             # Global styles + TailwindCSS
├── types.tsx             # Shared TypeScript type definitions
├── ping                  # Health check file (?)
├── Components/           # React UI components
│   ├── Index.tsx         # Main dashboard
│   ├── Login.tsx         # Authentication
│   ├── Game.tsx          # Pong game (1913 lines)
│   ├── Chat.tsx          # Main chat
│   ├── Profile.tsx       # User profile
│   ├── Settings.tsx      # Settings
│   ├── Matches.tsx       # Match history
│   ├── FriendsRequest.tsx # Friends management
│   ├── Tournamenst.jsx   # Tournaments
│   ├── Logout.tsx        # Session logout
│   └── Chat/             # Chat subcomponents (10 files)
├── Context/              # React Contexts (global state)
│   ├── AuthContext.tsx   # Authentication and user
│   ├── ComponentsContext.tsx # Socket.IO and notifications
│   └── TournamentContext.jsx # Tournament management
└── middleWare/           # Protected routes middleware
    └── middleWare.tsx    # ProtectedRoute component
```

## 🚀 Main Files

### `main.tsx` - Entry Point

**Purpose**: React application entry point. Renders the `App` component into the DOM.

```typescript
import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App.tsx'
import './index.css'

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
)
```

**Features**:
- **React.StrictMode**: Activates development warnings (double rendering, side effects detection)
- **root**: Mounts the app on the `<div id="root"></div>` element in `index.html`
- **TypeScript**: `.tsx` file with full type support

---

### `App.tsx` - Root Component

**Size**: ~404 lines  
**Purpose**: Main component that configures routing, contexts and application layout.

#### Structure

```typescript
import { BrowserRouter, Routes, Route, Navigate } from 'react-router-dom';
import { AuthProvider } from './Context/AuthContext';
import { ComponentsProvider } from './Context/ComponentsContext';
import { TournamentProvider } from './Context/TournamentContext';
import { ProtectedRoute } from './middleWare/middleWare';

// Components
import Login from './Components/Login';
import Index from './Components/Index';
import Game from './Components/Game';
import Chat from './Components/Chat';
import Profile from './Components/Profile';
import Settings from './Components/Settings';
import Matches from './Components/Matches';
import FriendsRequest from './Components/FriendsRequest';
import Tournamenst from './Components/Tournamenst';
import Logout from './Components/Logout';

function App() {
  return (
    <AuthProvider>
      <ComponentsProvider>
        <TournamentProvider>
          <BrowserRouter>
            <Routes>
              {/* Public route */}
              <Route path="/login" element={<Login />} />
              
              {/* Protected routes */}
              <Route
                path="/"
                element={
                  <ProtectedRoute>
                    <Layout />
                  </ProtectedRoute>
                }
              >
                <Route index element={<Index />} />
                <Route path="game" element={<Game />} />
                <Route path="tournament" element={<Tournamenst />} />
                <Route path="profile/:userId?" element={<Profile />} />
                <Route path="matches" element={<Matches />} />
                <Route path="friends" element={<FriendsRequest />} />
                <Route path="chat" element={<Chat />} />
                <Route path="settings" element={<Settings />} />
                <Route path="logout" element={<Logout />} />
              </Route>

              {/* Catch-all redirect */}
              <Route path="*" element={<Navigate to="/" replace />} />
            </Routes>
          </BrowserRouter>
        </TournamentProvider>
      </ComponentsProvider>
    </AuthProvider>
  );
}

// Layout with sidebar and outlet
function Layout() {
  return (
    <div className="flex h-screen bg-gray-900">
      <Sidebar />
      <main className="flex-1 overflow-auto">
        <Outlet />  {/* Renders active child route */}
      </main>
    </div>
  );
}

function Sidebar() {
  const { user } = useAuth();
  const navigate = useNavigate();

  return (
    <aside className="w-64 bg-gray-800 text-white p-4">
      <div className="mb-8">
        <h1 className="text-2xl font-bold">Transcendence</h1>
        <p className="text-sm text-gray-400">{user?.username}</p>
      </div>
      
      <nav className="space-y-2">
        <NavLink to="/">Dashboard</NavLink>
        <NavLink to="/game">Play</NavLink>
        <NavLink to="/tournament">Tournaments</NavLink>
        <NavLink to="/profile">Profile</NavLink>
        <NavLink to="/matches">History</NavLink>
        <NavLink to="/friends">Friends</NavLink>
        <NavLink to="/chat">Chat</NavLink>
        <NavLink to="/settings">Settings</NavLink>
        <NavLink to="/logout">Log Out</NavLink>
      </nav>
    </aside>
  );
}

export default App;
```

#### Features

- **React Router v7**: Component-based routing system
- **Nested Routes**: Shared layout for protected routes
- **Protected Routes**: Authentication middleware
- **Context Providers**: Cascading wrapping (Auth → Components → Tournament)
- **Lazy Loading**: Potential for `React.lazy()` in heavy components

---

### `types.tsx` - TypeScript Type Definitions

**Purpose**: Centralize all **interfaces and types** shared between components.

#### Main Types

```typescript
// types.tsx

// ========== USER ==========
export interface User {
  id: number;
  username: string;
  email: string;
  displayName: string;
  avatar?: string;
  bio?: string;
  stats: UserStats;
  createdAt: string;
  updatedAt: string;
}

export interface UserStats {
  wins: number;
  losses: number;
  winRate: number;
  elo: number;
  totalGames: number;
  currentStreak: number;
}

// ========== AUTHENTICATION ==========
export interface LoginCredentials {
  username: string;
  password: string;
}

export interface RegisterData extends LoginCredentials {
  email: string;
  displayName: string;
}

export interface AuthToken {
  token: string;
  refreshToken: string;
  expiresIn: number;
}

// ========== GAME ==========
export interface GameState {
  roomId: string;
  players: [Player, Player];
  ball: Ball;
  score: Score;
  status: GameStatus;
  timestamp: number;
}

export type GameStatus = 'waiting' | 'playing' | 'paused' | 'finished';

export interface Player {
  id: string;
  username: string;
  paddle: Paddle;
  isAI: boolean;
}

export interface Paddle {
  y: number;
  height: number;
  width: number;
  speed: number;
}

export interface Ball {
  x: number;
  y: number;
  vx: number;
  vy: number;
  radius: number;
  speed: number;
}

export interface Score {
  player1: number;
  player2: number;
}

// ========== MATCH ==========
export interface Match {
  id: number;
  player1: User;
  player2: User;
  winner: User;
  scorePlayer1: number;
  scorePlayer2: number;
  duration: number;  // seconds
  mode: MatchMode;
  replayData?: ReplayData;
  createdAt: string;
}

export type MatchMode = 'PvP' | 'AI' | 'Tournament';

export interface ReplayData {
  frames: GameState[];
  fps: number;
}

// ========== CHAT ==========
export interface Conversation {
  id: number;
  name?: string;
  isGroup: boolean;
  participants: User[];
  lastMessage?: Message;
  unreadCount: number;
  createdAt: string;
}

export interface Message {
  id: number;
  conversationId: number;
  sender: User;
  text: string;
  attachments?: string[];
  isEdited: boolean;
  createdAt: string;
}

export interface BlockedUser {
  id: number;
  blockedUser: User;
  createdAt: string;
}

// ========== FRIENDS ==========
export interface FriendRequest {
  id: number;
  sender: User;
  receiver: User;
  status: FriendRequestStatus;
  createdAt: string;
}

export type FriendRequestStatus = 'pending' | 'accepted' | 'rejected';

export interface Friendship {
  id: number;
  friend: User;
  isOnline: boolean;
  lastSeen?: string;
  createdAt: string;
}

// ========== TOURNAMENT ==========
export interface Tournament {
  id: string;
  name: string;
  players: User[];
  bracket: BracketNode[];
  currentRound: number;
  totalRounds: number;
  status: TournamentStatus;
  winner?: User;
  createdAt: string;
}

export type TournamentStatus = 'setup' | 'active' | 'finished';

export interface BracketNode {
  matchId: string;
  round: number;
  position: number;
  player1: User | null;
  player2: User | null;
  winner: User | null;
  nextMatchId: string | null;
}

// ========== NOTIFICATIONS ==========
export interface Notification {
  id: string;
  type: NotificationType;
  title: string;
  message: string;
  timestamp: number;
  duration?: number;
  action?: NotificationAction;
}

export type NotificationType = 'info' | 'success' | 'warning' | 'error';

export interface NotificationAction {
  label: string;
  onClick: () => void;
}

// ========== SOCKET.IO EVENTS ==========
export interface ServerToClientEvents {
  'gameUpdate': (state: GameState) => void;
  'gameOver': (result: MatchResult) => void;
  'new-message': (message: Message) => void;
  'user-typing': (data: { userId: number; username: string }) => void;
  'friend-request': (request: FriendRequest) => void;
  'friend-online': (data: { userId: number }) => void;
  'tournament-update': (bracket: BracketNode[]) => void;
  'notification': (notification: Notification) => void;
}

export interface ClientToServerEvents {
  'createRoom': (name: string, options: RoomOptions) => void;
  'joinRoom': (roomId: string) => void;
  'paddleMove': (data: { y: number }) => void;
  'send-message': (data: { conversationId: number; text: string }) => void;
  'join-chat': (conversationId: number) => void;
  'typing': (data: { conversationId: number }) => void;
}

export interface RoomOptions {
  mode: MatchMode;
  difficulty?: 'easy' | 'medium' | 'hard' | 'expert';
  maxPlayers?: number;
}

// ========== API RESPONSES ==========
export interface ApiResponse<T> {
  success: boolean;
  data?: T;
  error?: string;
  message?: string;
}

export interface PaginatedResponse<T> {
  data: T[];
  total: number;
  page: number;
  limit: number;
  hasMore: boolean;
}
```

---

### `index.css` - Global Styles

**Purpose**: Define global styles and TailwindCSS configuration.

```css
/* index.css */

/* Tailwind base, components, utilities */
@tailwind base;
@tailwind components;
@tailwind utilities;

/* Custom CSS variables */
:root {
  --color-primary: #3b82f6;
  --color-secondary: #8b5cf6;
  --color-success: #10b981;
  --color-danger: #ef4444;
  --color-warning: #f59e0b;
  --color-bg-dark: #111827;
  --color-bg-light: #1f2937;
}

/* Reset and base styles */
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

body {
  font-family: 'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', 
               'Roboto', 'Oxygen', 'Ubuntu', 'Cantarell', sans-serif;
  background-color: var(--color-bg-dark);
  color: white;
  line-height: 1.6;
}

/* Custom scrollbar */
::-webkit-scrollbar {
  width: 8px;
  height: 8px;
}

::-webkit-scrollbar-track {
  background: #1f2937;
}

::-webkit-scrollbar-thumb {
  background: #4b5563;
  border-radius: 4px;
}

::-webkit-scrollbar-thumb:hover {
  background: #6b7280;
}

/* Custom animations */
@keyframes fadeIn {
  from { opacity: 0; }
  to { opacity: 1; }
}

@keyframes slideIn {
  from { transform: translateY(-20px); opacity: 0; }
  to { transform: translateY(0); opacity: 1; }
}

.animate-fadeIn {
  animation: fadeIn 0.3s ease-in;
}

.animate-slideIn {
  animation: slideIn 0.4s ease-out;
}

/* Game canvas */
canvas {
  display: block;
  background: #000;
  border: 2px solid var(--color-primary);
  border-radius: 8px;
}

/* Smooth transitions */
button, a {
  transition: all 0.2s ease;
}

button:hover, a:hover {
  transform: translateY(-2px);
}

button:active, a:active {
  transform: translateY(0);
}
```

### `App.css` - App Component Styles

```css
/* App.css */

#root {
  width: 100%;
  height: 100vh;
  overflow: hidden;
}

.sidebar {
  box-shadow: 2px 0 10px rgba(0, 0, 0, 0.5);
}

.nav-link {
  display: flex;
  align-items: center;
  gap: 12px;
  padding: 12px 16px;
  border-radius: 8px;
  text-decoration: none;
  color: #d1d5db;
  font-weight: 500;
}

.nav-link:hover {
  background-color: #374151;
  color: white;
}

.nav-link.active {
  background-color: #3b82f6;
  color: white;
}

.main-content {
  padding: 24px;
  overflow-y: auto;
}
```

---

### `ping` - Health Check File

**Purpose**: File likely used for health checks or testing (content unknown without reading).

**Note**: Could be a plain text file with "pong" as a response, or a script. Requires verification.

---

## 🔗 Initialization Flow

```
1. Browser loads index.html
      ↓
2. Vite loads main.tsx
      ↓
3. ReactDOM.createRoot renders <App />
      ↓
4. <AuthProvider> mounts
      ↓
   - Verifies token in localStorage
   - Calls /api/auth/verify
   - Sets user if token is valid
      ↓
5. <ComponentsProvider> mounts
      ↓
   - Initializes Socket.IO with token
   - Registers global event handlers
      ↓
6. <TournamentProvider> mounts
      ↓
   - Initializes tournament state
      ↓
7. <BrowserRouter> activates routing
      ↓
8. If user authenticated → Layout + active route
   If not authenticated → Redirect to /login
```

## 📦 Build Tool Integration (Vite)

```javascript
// vite.config.js (in /frontend/)
import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

export default defineConfig({
  plugins: [react()],
  server: {
    port: 5173,
    host: true,  // Required for Docker
    proxy: {
      '/api': {
        target: 'http://localhost:3000',
        changeOrigin: true
      },
      '/socket.io': {
        target: 'http://localhost:3000',
        ws: true
      }
    }
  },
  build: {
    outDir: 'dist',
    sourcemap: true
  }
})
```

## 🧪 Testing

```bash
# Unit tests
npm test src/Components/Login.test.tsx

# Component tests with Testing Library
npm test src/Components/Game.test.tsx

# E2E with Cypress
npx cypress run --spec "cypress/e2e/full-game-flow.cy.ts"
```

---

**Location**: `/frontend/src/`  
**Technologies**: React 19, TypeScript, React Router v7, TailwindCSS  
**Related documentation**:
- `Components/README.md` - Component details
- `Context/README.md` - Global contexts
- `middleWare/README.md` - Protected routes
- `/backend/` - Consumed REST API