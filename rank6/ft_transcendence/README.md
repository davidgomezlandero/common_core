<div align="center">

# 🎮 Transcendence

### *The Ultimate Pong of the 21st Century*

[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://www.42malaga.com/)
[![TypeScript](https://img.shields.io/badge/TypeScript-007ACC?style=for-the-badge&logo=typescript&logoColor=white)](https://www.typescriptlang.org/)
[![React](https://img.shields.io/badge/React_19-20232A?style=for-the-badge&logo=react&logoColor=61DAFB)](https://react.dev/)
[![Node.js](https://img.shields.io/badge/Node.js_20-43853D?style=for-the-badge&logo=node.js&logoColor=white)](https://nodejs.org/)
[![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)](https://www.docker.com/)

**A real-time multiplayer gaming experience with cutting-edge technologies**

by davigome, jesopan-, nporras-, rdel-olm & sternero (2025)

[🚀 Quick Start](#-quick-start) • [📚 Documentation](#-full-documentation) • [🏗️ Architecture](#-system-architecture) • [🎯 Features](#-main-features)

---

</div>

## 📋 Project Description

**Transcendence** is a modern implementation of the classic **Pong** game, transformed into a full multiplayer gaming platform with:

- 🤖 **Advanced Artificial Intelligence** with 4 difficulty levels
- 🌐 **Real-time multiplayer** via WebSockets
- 🏆 **Tournament system** with elimination brackets
- 💬 **Integrated chat** with instant messaging
- 👥 **Complete social system** (friends, profiles, statistics)
- 🔒 **Enterprise-level security** (WAF, Vault, SSL/TLS)
- 🎨 **Modern UI/UX** with animations and visual effects

> 🎓 **42 School final project** - Developed as the culmination of the full-stack web development curriculum

---

## 🚀 Quick Start

### Prerequisites

- **Node.js** 20+ and npm
- **Docker** and Docker Compose (optional but recommended)
- **SQLite** (created automatically)
- **OAuth 2.0 credentials** from Google (optional for social login)

### Express Installation (5 minutes)

```bash
# 1. Clone the repository
git clone https://github.com/...
cd transcendence

# 2. Initialize infrastructure (SSL certificates + Vault + WAF)
make init

# 3. Install backend dependencies
npm install

# 4. Install frontend dependencies
cd frontend && npm install && cd ..

# 5. Start everything with Docker Compose
docker-compose up -d

# 6. Or start manually:
# Terminal 1 - Backend
npm start

# Terminal 2 - Frontend
cd frontend && npm run dev
```

### Application Access

- 🎮 **Frontend**: http://localhost:5173
- 🔧 **Backend API**: http://localhost:3000
- 🔐 **Vault UI**: http://localhost:8200
- 📊 **Nginx Status**: http://localhost/nginx_status

---

## 🏗️ System Architecture

### 📊 Full Technology Stack

<table>
<tr>
<td width="50%">

#### Frontend
- ⚛️ **React 19** with React Compiler
- 🔷 **TypeScript 5.7** for type-safety
- ⚡ **Vite 6** as build tool
- 🎨 **TailwindCSS 4** for styling
- 🔌 **Socket.IO Client** for WebSockets
- 🧭 **React Router 7** for SPA routing

</td>
<td width="50%">

#### Backend
- 🚀 **Fastify 4** as HTTP framework
- 🔌 **Socket.IO 4** for real-time
- 🗄️ **Sequelize 6** as ORM
- 💾 **SQLite 3** for database
- 🔐 **bcrypt** for password hashing
- 🎫 **JWT** for authentication

</td>
</tr>
<tr>
<td width="50%">

#### Infrastructure
- 🐳 **Docker Compose** for orchestration
- 🌐 **Nginx** as reverse proxy
- 🛡️ **ModSecurity WAF** with OWASP CRS
- 🔒 **HashiCorp Vault** for secrets
- 📜 **SSL/TLS** with self-signed certificates

</td>
<td width="50%">

#### Development
- 📦 **npm** for package management
- 🔧 **nodemon** for auto-reload
- 🧪 **Vitest** for testing
- 📝 **ESLint** for linting
- 🎯 **TypeScript** throughout the project

</td>
</tr>
</table>

### 🔄 Architecture Flow

```
┌──────────────┐         HTTPS          ┌────────────┐
│   Client     │ ────────────────────►  │   Nginx    │
│   Browser    │                        │   :443     │
└──────────────┘                        └─────┬──────┘
                                              │
                                ┌─────────────┴─────────────┐
                                │                           │
                          ┌─────▼──────┐             ┌──────▼─────┐
                          │ ModSecurity│             │  Frontend  │
                          │    WAF     │             │  React:80  │
                          └─────┬──────┘             └────────────┘
                                │
                    ┌───────────┴───────────┐
                    │                       │
              ┌─────▼─────┐          ┌──────▼──────┐
              │  Backend  │          │  Socket.IO  │
              │Fastify:300│◄─────────┤   Server    │
              └─────┬─────┘          └─────────────┘
                    │
        ┌───────────┼──────────┐
        │           │          │
   ┌────▼────┐  ┌───▼───┐  ┌───▼────┐
   │ SQLite  │  │ Vault │  │  Logs  │
   │   DB    │  │ :8200 │  │  /logs │
   └─────────┘  └───────┘  └────────┘
```

### 📁 Project Structure

```
transcendence/
├── 📂 backend/                   # Node.js Server
│   ├── pon-server.js             # Main server (1071 lines)
│   ├── auth.js                   # JWT + OAuth authentication (522 lines)
│   ├── chat.js                   # Chat system (376 lines)
│   ├── db.js                     # Sequelize models
│   └── README.md                 # 📚 Detailed documentation
│
├── 📂 frontend/                   # React Application
│   ├── src/
│   │   ├── main.tsx              # Entry point
│   │   ├── App.tsx               # Root component (404 lines)
│   │   ├── Components/           # 11 components
│   │   │   ├── Game.tsx          # Pong game (1913 lines)
│   │   │   ├── Chat.tsx          # Main chat
│   │   │   └── Chat/             # 10 subcomponents
│   │   ├── Context/              # Global contexts
│   │   ├── middleWare/           # Protected routes
│   │   └── types.tsx             # TypeScript types
│   └── README.md                 # 📚 Frontend documentation
│
├── 📂 srcs/                       # Infrastructure
│   ├── conf/                     # Configurations
│   │   ├── nginx/                # Reverse proxy
│   │   └── modsecurity/          # WAF + OWASP CRS
│   ├── scripts/                  # Automation scripts
│   ├── secrets/                  # Secrets management
│   │   ├── certs/                # SSL certificates
│   │   ├── vault/                # Vault keys
│   │   └── api-approle/          # AppRole credentials
│   ├── data/                     # Persistent data
│   └── logs/                     # Service logs
│
├── docker-compose.yml            # Service orchestration
├── Makefile                      # Automation commands
└── README.md                     # 👈 You are here

📚 Each directory includes a detailed README.md with examples and full documentation
```

---

## 🎯 Main Features

### 🎮 Game System

<table>
<tr>
<td width="33%">

#### 🤖 Advanced AI
- 4 difficulty levels
- Trajectory prediction
- Realistic reaction times
- Calculated errors per level

</td>
<td width="33%">

#### 🏓 Realistic Physics
- Precise collision system
- Gradual ball acceleration
- Spin effect on impacts
- 60 FPS update rate

</td>
<td width="33%">

#### 🎬 Replay System
- Automatic recording
- Play/pause/speed controls
- Match analysis
- Data export

</td>
</tr>
</table>

### 👥 Social System

- 🤝 **Friends System**: Send requests, accept/reject, see online status
- 💬 **Real-time Chat**: Private conversations, groups, instant messages
- 🚫 **User Blocking**: Blocked list with automatic filtering
- 📊 **Custom Profiles**: Avatar, bio, statistics, match history
- 🏆 **Rankings and ELO**: Competitive ranking system

### 🔐 Enterprise Security

- 🛡️ **ModSecurity WAF**: Protection against XSS, SQLi, LFI, RFI, RCE
- 🔒 **HashiCorp Vault**: Centralized secrets management
- 📜 **SSL/TLS**: End-to-end encryption
- 🎫 **JWT + Refresh Tokens**: Secure stateless authentication
- 🔑 **OAuth 2.0**: Login with Google (optional)
- 🚦 **Rate Limiting**: Protection against brute-force and DDoS

### 🏆 Tournament System

- 🗓️ **Tournament Creation**: Single elimination brackets
- 🎯 **Automatic Progression**: Winners advance automatically
- 📊 **Bracket Visualization**: Interactive tournament chart
- 🎉 **Victory Celebration**: Confetti animation for the champion

---

## 🔧 Detailed Configuration

### Environment Variables

## 🏗️ System Architecture


## Environment variables

Create a `.env` file in the project root:

```
# Backend
JWT_SECRET=supersecretkey               # change in production

# Google OAuth (optional)
GOOGLE_CLIENT_ID=your-google-client-id
GOOGLE_CLIENT_SECRET=your-google-client-secret
GOOGLE_CALLBACK_URL=http://localhost:3000/auth/google/callback

# Frontend URL for post-login redirect (used by Google flow)
FRONTEND_URL=http://localhost:2323/login
```

Notes:
- `pon-server.js` currently uses a default secret `'supersecretkey'`; setting `JWT_SECRET` is recommended.
- `FRONTEND_URL` is where the backend redirects with `#token=...` after Google login.
- CORS for Socket.IO is already configured for `http://localhost:2323`.


## Install and run

### Backend (API + Socket.IO)

From the repository root:

```bash
npm install
npm start               # starts Fastify + Socket.IO on :3000
```

Useful backend scripts (root `package.json`):
- `start` – run the server (`pon-server.js`)
- `dev` – watch Tailwind, TS, and start the server together
- `build:css` – Tailwind build from `src/input.css` to `public/style.css`
- `build:ts` / `build:ts-once` – TypeScript compile for non‑React pages

The database file will be created at `backend/database.sqlite` on first run.

### Frontend (React + Vite)

In a second terminal:

```bash
cd frontend
npm install
npm run dev           # Vite dev server on :2323
```

Vite is configured to proxy API calls to `http://localhost:3000` (see `frontend/vite.config.js`).


## Features

- JWT auth (login, logout, me) and Google OAuth 2.0 flow
- Friends system (requests, accept/reject, online/offline signals)
- Real‑time game rooms via Socket.IO (1v1 and AI mode with difficulty)
- Match persistence + basic player stats (wins/losses)
- Tailwind styling, React components, and WebSocket‑driven UI updates


## Key API routes (Fastify)

All routes are defined in `pon-server.js` and implemented in `backend/auth.js`.

- `POST /api/auth/register` – Create user (username/password)
- `POST /api/auth/login` – Returns `{ token, user }` on success
- `POST /api/auth/logout` – Requires JWT (bearer). Ends one session
- `GET /api/auth/me` – Returns current user profile

- `GET /api/user/profile/:userId` – Public profile + last matches
- `PUT /api/user/profile` – Update own profile
- `PUT /api/user/profile/changePassword` – Change password

- `GET /api/user/friends` – List accepted friends
- `GET /api/user/friend-getFriendRequests` – Pending requests for me
- `POST /api/user/friend-request` – Send friend request by username
- `POST /api/user/friend-response` – Accept/Reject request

- `GET /api/user/match-history` – My match history (latest first)

- `GET /auth/google/callback` – Google OAuth callback (internal in flow)

Auth: send JWT as `Authorization: Bearer <token>` for protected routes.


## Socket.IO events (high level)

Client → Server:

---

## 🧪 Testing and Validation

### Backend Testing

```bash
# Unit tests
npm test

# Authentication test
curl -X POST http://localhost:3000/api/auth/login \
  -H "Content-Type: application/json" \
  -d '{"username":"test","password":"test123"}'
```

### Security Testing (ModSecurity WAF)

```bash
# Run security test suite
./srcs/scripts/99.test_modsec_rules.sh
```

---

## 🚨 Troubleshooting

### Common Issues

- **EADDRINUSE**: Kill process with `lsof -ti:3000 | xargs kill -9`
- **JWT invalid**: Clear localStorage and re-login
- **Vault sealed**: Use `vault operator unseal` with key from `/srcs/secrets/vault/unseal_key`
- **ModSecurity blocking**: Adjust `paranoia_level` in `crs-setup.conf`

---

## 📚 Full Project Documentation

### 📁 General
- [Main README](./README.md) - This file (general project information)

### 🔧 Backend
- [Backend README](./backend/README.md) - Full Node.js server documentation
- [AI Implementation README](./backend/AI_IMPLEMENTATION.md) - Artificial Intelligence module (4 levels, spin, counter-spin)
- [Blockchain README](./backend/blockchain/README.md) - Smart contracts and blockchain services
- [Hardhat README](./backend/blockchain/hardhat/README.md) - Hardhat development environment
- [Solidity Contracts README](./backend/blockchain/hardhat/contracts/README.md) - TournamentRegistry smart contract
- [Deploy Scripts README](./backend/blockchain/hardhat/scripts/README.md) - Avalanche deployment scripts

### 🎨 Frontend
- [Frontend README](./frontend/README.md) - Full React 19 + TypeScript + Vite client
- [Source Code README](./frontend/src/README.md) - Application source code
- [Components README](./frontend/src/Components/README.md) - All React components
- [Chat README](./frontend/src/Components/Chat/README.md) - Real-time messaging system
- [Context README](./frontend/src/Context/README.md) - Global state management (AuthContext, etc.)
- [Middleware README](./frontend/src/middleWare/README.md) - Protected routes and authentication
- [Services README](./frontend/src/services/README.md) - API services layer (blockchainService, etc.)
- [Static Assets README](./frontend/static/README.md) - Static files served by Nginx

### 🛡️ Infrastructure
- [Srcs README](./srcs/README.md) - Service configuration and infrastructure
- [Configuration README](./srcs/conf/README.md) - Nginx + ModSecurity + WAF
- [Scripts README](./srcs/scripts/README.md) - Initialization and maintenance scripts
- [Secrets README](./srcs/secrets/README.md) - Centralized sensitive information management
- [Vault README](./srcs/secrets/vault/README.md) - HashiCorp Vault (tokens and keys)
- [API AppRole README](./srcs/secrets/api-approle/README.md) - Vault authentication for backend
- [Certificates README](./srcs/secrets/certs/README.md) - SSL/TLS certificates

### 📊 Testing and Validation
- [test_auto.sh](./test_auto.sh) - Automatic validation script v3.0
- [test_result.md](./test_result.md) - Validation report (auto-generated)

### 🔗 Quick Navigation by Module

#### Game Development
- 🎮 [Game Logic](./backend/pon-server.js) - Game server (1071 lines)
- 🤖 [AI Documentation](./backend/AI_IMPLEMENTATION.md) - AI algorithms
- 🎨 [Game Component](./frontend/src/Components/Game.tsx) - Game client (1913 lines)

#### Authentication and Security
- 🔐 [Auth Backend](./backend/auth.js) - JWT + OAuth2 (522 lines)
- 🛡️ [ModSecurity Config](./srcs/conf/modsecurity/) - WAF rules
- 🔒 [Vault Setup](./srcs/secrets/vault/README.md) - Secrets management

#### Chat and Social
- 💬 [Chat Backend](./backend/chat.js) - Chat logic (376 lines)
- 💬 [Chat Frontend](./frontend/src/Components/Chat/README.md) - Chat components
- 👥 [User Management](./backend/db.js) - Database models

#### Blockchain and Tournaments
- ⛓️ [Smart Contract](./backend/blockchain/hardhat/contracts/README.md) - TournamentRegistry.sol
- 🚀 [Deploy Scripts](./backend/blockchain/hardhat/scripts/README.md) - Fuji deployment
- 🎯 [Tournament Component](./frontend/src/Components/Tournaments.tsx) - Tournament UI

---

## 📜 License

MIT License - See [LICENSE](LICENSE)

---

## 👥 Authors

**Team: davigome, jesopan-, nporras-, rdel-olm & sternero - 42 Málaga (2025)**

---

<div align="center">

### ⭐ Give it a star if you like the project ⭐

**Made with ❤️ by the Transcendence042 team**

</div>