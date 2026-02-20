# 🎨 Frontend - React Client for the Transcendence Project

## 📋 General Overview

This directory contains the complete **frontend client** of the Transcendence application. It implements a modern SPA (Single Page Application) with **React 19** + **TypeScript** + **Vite** + **Tailwind CSS**.

## 🗂️ Project Structure

```
frontend/
├── index.html              # HTML entry point
├── vite.config.js          # Vite configuration
├── tsconfig.json           # TypeScript configuration
├── tailwind.config.js      # Tailwind CSS configuration
├── postcss.config.js       # PostCSS configuration
├── package.json            # Dependencies and scripts
├── Dockerfile              # Frontend Docker image
├── healthz                 # Health check endpoint
├── ping                    # Ping endpoint
├── public/                 # Static assets
├── static/                 # Additional static files
├── dist/                   # Production build (generated)
└── src/                    # Source code
    ├── main.tsx           # Application entry point
    ├── App.tsx            # Root component
    ├── App.css            # App styles
    ├── index.css          # Global styles
    ├── types.tsx          # TypeScript type definitions
    ├── Components/        # React components (see internal README)
    ├── Context/           # Context API for global state
    ├── middleWare/        # Middleware and utilities
    └── services/          # Services (API, blockchain, etc.)
```

## 🚀 Main Technologies

### Core
- **React 19.1.1** - UI library with the latest features
- **TypeScript 5.9.3** - Static typing for JavaScript
- **Vite 7.1.7** - Ultra-fast build tool with HMR

### Styles
- **Tailwind CSS 3.3.5** - Utility-first CSS framework
- **PostCSS 8.5.6** - CSS processor
- **Autoprefixer 10.4.21** - Automatic CSS prefixes

### Routing & State
- **React Router DOM 7.9.4** - SPA navigation
- **Context API** - Global state management

### Communication
- **Socket.IO Client 4.8.1** - WebSockets for real-time
- **Fetch API** - HTTP requests to the backend

### Extras
- **React Icons 5.5.0** - Icons
- **React Confetti 6.4.0** - Celebration effects

## 📦 Available Scripts

```bash
# Development
npm run dev              # Starts development server on port 2323
npm start                # Alias for development (port 2323)

# Production
npm run build            # Compiles for production in /dist
npm run preview          # Preview of the production build

# Code quality
npm run typecheck        # Verifies TypeScript types without compiling
```

## 🏗️ Frontend Architecture

### Main Components

```
src/Components/
├── Login.tsx              # Login screen and OAuth
├── Logout.tsx             # Session logout
├── Index.tsx              # Main dashboard
├── Game.tsx               # Pong game component
├── Matches.tsx            # Matchmaking system
├── Tournaments.tsx        # Tournament management
├── Profile.tsx            # User profile
├── Settings.tsx           # Account settings
├── FriendsRequest.tsx     # Friends management
└── Chat/                  # Complete chat system
    ├── ChatMain.tsx
    ├── ChatHeader.tsx
    ├── ChatSideBar.tsx
    ├── MessageInput.tsx
    ├── ConversationList.tsx
    ├── BlockUser.tsx
    └── BlockedUsersList.tsx
```

### State Management (Context API)

```
src/Context/
├── AuthContext.tsx         # Authentication and user
├── ComponentsContext.tsx   # Component state
└── TournamentContext.tsx   # Tournament state
```

### Middleware

```
src/middleWare/
└── middleWare.tsx          # Route protection, validations
```

### Services

```
src/services/
└── blockchainService.ts    # Interaction with smart contracts
```

## 🎨 Styling System

### Tailwind CSS

The project uses **Tailwind CSS** for utility-first styles. Configuration in `tailwind.config.js`:

```javascript
// Responsive breakpoints
sm: '640px'   // Mobile landscape
md: '768px'   // Tablet
lg: '1024px'  // Desktop
xl: '1280px'  // Large desktop
2xl: '1536px' // Extra large
```

### Custom CSS

- `App.css` - App component-specific styles
- `index.css` - Global styles and Tailwind imports

## 🔌 Backend Communication

### HTTP Requests

```typescript
// Example request to the backend
const response = await fetch('http://localhost:3000/api/auth/login', {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  credentials: 'include',
  body: JSON.stringify({ username, password })
});
```

### WebSockets (Socket.IO)

```typescript
import io from 'socket.io-client';

// Connect to server
const socket = io('http://localhost:3000', {
  withCredentials: true,
  transports: ['websocket', 'polling']
});

// Events
socket.emit('joinRoom', { roomId });
socket.on('gameUpdate', (data) => { /* ... */ });
```

## 🔐 Authentication

### Login Flow

1. **Standard Login**: Username/password → `/api/auth/login`
2. **OAuth 2.0**: Google/42 → `/api/auth/google` → Callback
3. **Session**: Secure HttpOnly cookie with JWT
4. **Context**: Global state in `AuthContext`

### Protected Routes

The middleware verifies authentication before rendering private components:

```typescript
// middleWare.tsx
if (!isAuthenticated) {
  return <Navigate to="/login" />;
}
```

## 🎮 Frontend Features

### Game System

- **Canvas Rendering**: Pong game in HTML5 Canvas
- **Real-time Updates**: Socket.IO for synchronization
- **AI Levels**: 4 difficulty levels
- **Replay System**: Recording and playback of matches
- **Spectator Mode**: Watch live matches

### Chat

- **Direct Messaging**: 1-to-1 conversations
- **Rooms/Channels**: Group chat rooms
- **User Blocking**: Blocked users list
- **Notifications**: Unread messages
- **Emojis**: Emoji support

### Profile & Social

- **Statistics**: Win/Loss ratio, ranking
- **Match History**: Recent matches
- **Friends System**: Requests and friends list
- **Avatar**: Profile image upload
- **Customization**: Nickname, preferences

### Tournaments

- **Creation**: Create tournaments with brackets
- **Registration**: Join tournaments
- **Visualization**: View brackets in real time
- **Blockchain**: Registration in smart contract

## 🐳 Docker

### Dockerfile

```dockerfile
FROM node:20-alpine
WORKDIR /app
COPY package*.json ./
RUN npm ci
COPY . .
EXPOSE 2323
CMD ["npm", "run", "dev"]
```

### Environment Variables

```bash
PORT=2323                              # Development server port
VITE_BACKEND_URL=http://localhost:3000 # Backend URL
```

## 🔧 Development Configuration

### Vite Configuration

```javascript
// vite.config.js
export default {
  server: {
    port: 2323,
    host: '0.0.0.0',
    proxy: {
      '/api': 'http://localhost:3000'
    }
  }
}
```

### TypeScript Configuration

```json
// tsconfig.json
{
  "compilerOptions": {
    "target": "ES2020",
    "jsx": "react-jsx",
    "module": "ESNext",
    "strict": true
  }
}
```

## 🚀 Quick Start

### Local Development

```bash
# Install dependencies
npm install

# Start development server
npm run dev

# Open in browser
# http://localhost:2323
```

### Production

```bash
# Build for production
npm run build

# Preview the build
npm run preview
```

### Docker

```bash
# Build image
docker build -t transcendence-frontend .

# Run container
docker run -p 2323:2323 transcendence-frontend
```

## 📝 Code Conventions

### Components

- **PascalCase** for component names
- **camelCase** for functions and variables
- **TypeScript** for all code
- **Props interface** for each component

```typescript
interface GameProps {
  roomId: string;
  isSpectator: boolean;
}

const Game: React.FC<GameProps> = ({ roomId, isSpectator }) => {
  // ...
}
```

### Hooks

- Use React hooks (useState, useEffect, useContext)
- Custom hooks with `use` prefix
- Extract complex logic into custom hooks

### Styles

- **Tailwind classes** as first option
- CSS modules for specific styles
- Avoid inline styles except in exceptional cases

## 🧪 Testing

```bash
# Verify TypeScript types
npm run typecheck

# Lint
npm run lint

# Build test
npm run build
```

## 📚 Additional Documentation

- [README Components](./src/Components/README.md) - Component documentation
- [README Chat](./src/Components/Chat/README.md) - Chat system
- [README Context](./src/Context/README.md) - State management
- [README Middleware](./src/middleWare/README.md) - Frontend middleware

## 📄 License

This project is part of the **42 School Málaga** curriculum (2025)

---

**🎮 Transcendence Frontend** - Version 1.0.0  
*Last updated: December 2025*