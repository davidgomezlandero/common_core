# 🎮 Components - React Components of the Application

## 📋 General Overview

This directory contains all the **React components** that make up the user interface of the Transcendence application. Each component represents a complete functional section of the SPA (Single Page Application), implementing modern React patterns with TypeScript.

## 🗂️ Component Structure

### 🎯 Navigation and Layout Components

#### `Index.tsx`
**Purpose**: Home page/dashboard for the authenticated user.

**Features**:
- Personal statistics summary
- Recent matches list
- Quick access to main features
- Notifications and friends activity

**State**: Reads data from `AuthContext` to personalize the dashboard.

---

#### `Login.tsx`
**Purpose**: User authentication form.

**Features**:
- Login with username/email + password
- Real-time field validation
- Error handling (invalid credentials)
- Post-login redirect to protected route
- Optional: OAuth login (Google, 42)

**Flow**:
```typescript
1. User enters credentials
2. submit() → POST /api/auth/login
3. Backend verifies with bcrypt
4. Backend returns JWT token
5. Frontend stores token in AuthContext
6. Redirect to /index
```

**Security**: Does not store passwords in state; sends directly to backend.

---

#### `Logout.tsx`
**Purpose**: Session logout and state cleanup.

**Process**:
1. Calls `POST /api/auth/logout`
2. Backend invalidates token (blacklist)
3. Frontend clears `AuthContext.user`
4. Clears localStorage/sessionStorage
5. Redirect to `/login`

**Note**: Can be a component or simply a function in `AuthContext`.

---

### 👤 User Components

#### `Profile.tsx`
**Purpose**: User profile display and editing.

**Sections**:
- **Personal Info**: Avatar, username, displayName, bio
- **Statistics**: Wins, losses, win rate, ELO/ranking
- **History**: Last 10 played matches
- **Friends**: Friends list with online status

**Editing**:
- Modal or inline edit mode
- Avatar change (image upload)
- Bio/displayName update

**API**:
```typescript
GET  /api/users/:id          // View profile
PUT  /api/users/me/profile   // Edit own profile
POST /api/users/avatar       // Avatar upload
```

---

#### `Settings.tsx`
**Purpose**: Account settings and preferences.

**Options**:
- **Account**: Change password, email
- **Privacy**: Public/private profile, show activity
- **Notifications**: Enable/disable by type
- **Appearance**: Light/dark theme, language
- **Advanced**: Enable 2FA, download data, delete account

**Persistence**: Changes are saved automatically or with a "Save" button.

---

#### `FriendsRequest.tsx`
**Purpose**: Friend request management.

**Features**:
- **Pending**: Received requests (accept/reject)
- **Sent**: Sent requests (cancel)
- **Search users**: Input to send new requests
- **Recommendations**: Suggested users to add

**Real-time**: Uses Socket.IO to notify new requests immediately.

---

### 🎮 Game Components

#### `Game.tsx`
**Purpose**: Main Pong game interface.

**Features** (main file of ~1900 lines):
- Game rendering canvas
- Paddle control with keyboard (↑/↓ or W/S)
- Particle system for visual effects
- Procedural audio with Web Audio API
- Real-time statistics (hits, speed, rally)
- Replay system with controls (play/pause/speed)
- Opponent selector (AI/Human)
- 4 AI difficulty levels
- End-of-game modal with results

**Communication**: Bidirectional Socket.IO with `backend/pon-server.js`.

**Extended documentation**: See `AI.md`, `S_IMPLEMENTACIONES.md`, `AI_EVALUATION.md` in the project root.

---

#### `Tournamenst.jsx`
**Purpose**: Elimination tournament system.

**Features**:
- Tournament creation with N players (powers of 2)
- Graphically visualized bracket
- Round management (semifinals, final)
- Automatic progress after each match
- Winner highlighted with confetti

**Technology**:
- React Context: `TournamentContext.jsx`
- Animations: `react-confetti`
- Canvas to draw bracket

**Flow**:
```
1. Create tournament → Wait for players
2. Start → Generate bracket
3. First round → 4 simultaneous matches
4. Winners advance → Second round
5. Final → Determine champion
```

---

### 📊 Data Components

#### `Matches.tsx`
**Purpose**: Complete match history of the user.

**Display**:
- Table or list of matches
- Filters: Date, opponent, result (win/loss)
- Sorting: Most recent, oldest
- Pagination: 20 matches per page

**Data shown**:
- Date and time
- Opponent (name + avatar)
- Result (4-2, 5-3, etc.)
- Match duration
- Statistics: Total hits, max speed

**Export**: Button to download CSV with complete history.

---

### 💬 Chat Component

#### `Chat.tsx`
**Purpose**: Instant messaging interface.

**Architecture**:
- Container component that orchestrates subcomponents
- Delegates rendering to components in the `Chat/` directory
- Manages global state of the active chat

**Subcomponents**: See [Chat/README.md](./Chat/README.md) for full details on:
- ChatMain, ChatSideBar, MessagesList, MessageInput
- ChatHeader, ConversationList, NewChat
- ShowProfile, BlockUser, BlockedUsersList

**Communication**: Socket.IO with events `send-message`, `new-message`, `typing`.

---

## 🔄 Navigation Flow

```
App.tsx (root)
  ├─→ Login.tsx (if not authenticated)
  │
  └─→ Layout with sidebar (if authenticated)
       ├─→ Index.tsx (default)
       ├─→ Game.tsx
       ├─→ Tournamenst.jsx
       ├─→ Profile.tsx
       ├─→ Matches.tsx
       ├─→ FriendsRequest.tsx
       ├─→ Chat.tsx
       ├─→ Settings.tsx
       └─→ Logout.tsx
```

## 🎨 Patterns and Technologies

### Hooks Used

```typescript
// Local state
useState<T>(initialValue)

// Side effects (fetch, sockets)
useEffect(() => {...}, [deps])

// Global contexts
useContext(AuthContext)
useContext(ComponentContext)
useContext(TournamentContext)

// DOM references
useRef<HTMLCanvasElement>(null)

// Programmatic navigation
const navigate = useNavigate()
```

### State Management

```
Local State (useState)
    ↓
Global Contexts (Context API)
    ├─→ AuthContext: user, token, logout
    ├─→ ComponentsContext: socket, rooms, notifications
    └─→ TournamentContext: currentTournament, bracket
    ↓
Backend State (REST API + Socket.IO)
```

### Styling

- **TailwindCSS**: Utility-first CSS framework
- **Dynamic classes**: `className={isActive ? 'bg-blue-500' : 'bg-gray-300'}`
- **Animations**: Tailwind transitions + custom CSS animations
- **Responsive**: Breakpoints `sm:`, `md:`, `lg:`, `xl:`

## 🔗 Backend Integration

### REST API Endpoints

Each component consumes specific endpoints:

```typescript
// Login.tsx
POST /api/auth/login
POST /api/auth/register

// Profile.tsx
GET  /api/users/:id
PUT  /api/users/me/profile

// Matches.tsx
GET  /api/matches?userId=:id&limit=20&offset=0

// FriendsRequest.tsx
GET  /api/friends/requests
POST /api/friends/send
PUT  /api/friends/respond/:id

// Settings.tsx
PUT  /api/users/me/settings
POST /api/users/me/change-password

// Chat.tsx
GET  /api/conversations
GET  /api/messages/:conversationId
POST /api/conversations/create
```

### Socket.IO Events

Real-time components:

```typescript
// Game.tsx
socket.emit('createRoom', roomName, { mode: 'AI' })
socket.emit('paddleMove', { y: newY })
socket.on('gameUpdate', (gameState) => {...})

// Chat.tsx
socket.emit('join-chat', conversationId)
socket.emit('send-message', { text })
socket.on('new-message', (message) => {...})

// FriendsRequest.tsx
socket.on('friend-request', (request) => {...})
socket.on('friend-online', ({ userId }) => {...})

// Tournamenst.jsx
socket.emit('join-tournament', tournamentId)
socket.on('tournament-started', (bracket) => {...})
socket.on('match-ended', ({ winner }) => {...})
```

## 📦 Main Dependencies

```json
{
  "react": "^19.1.1",
  "react-dom": "^19.1.1",
  "react-router-dom": "^7.9.4",
  "socket.io-client": "^4.8.1",
  "react-icons": "^5.5.0",
  "react-confetti": "^6.4.0"
}
```

## 🧪 Testing

```bash
# Component unit tests
npm test Components/Login.test.tsx

# Integration tests with API mock
npm test Components/Game.integration.test.tsx

# E2E tests with Cypress
npx cypress run --spec "cypress/e2e/game-flow.cy.ts"
```

## 🚀 Future Improvements

### Optimization
- [ ] Lazy loading of heavy components (`React.lazy`)
- [ ] Component memoization with `React.memo`
- [ ] Long list virtualization (`react-window`)

### Features
- [ ] PWA: Push notifications
- [ ] Offline mode with data cache
- [ ] Share matches on social networks
- [ ] Achievements system

### Accessibility
- [ ] Complete ARIA labels
- [ ] Keyboard navigation
- [ ] Screen reader support
- [ ] High contrast and large text

---

**Location**: `/frontend/src/Components/`  
**Technologies**: React 19, TypeScript, TailwindCSS, Socket.IO Client  
**Related documentation**:
- [Chat/README.md](./Chat/README.md) - Messaging subcomponents
- `../Context/README.md` - Global contexts
- `../types.tsx` - Shared TypeScript interfaces
- `/AI.md`, `/S_IMPLEMENTACIONES.md` - Game AI documentation