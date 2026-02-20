# 📂 Backend - Node.js Server for Transcendence Project

## 📋 General Description

This directory contains the complete **backend server** for the Transcendence application. It implements an architecture based on **Fastify** (fast HTTP framework) + **Socket.IO** (real-time communication) + **Sequelize ORM** (SQLite database management).

## 🗂️ File Structure

```
backend/
├── pon-server.js         # Main server (1071 lines)
├── auth.js               # Authentication and OAuth (522 lines)
├── chat.js               # Chat and messaging system (376 lines)
├── db.js                 # Database configuration and models
├── index.js              # Entry point (runs pon-server.js)
├── package.json          # Dependencies and scripts
├── nodemon.json          # Auto-reload configuration
├── Dockerfile            # Backend Docker image
├── srcs/                 # Additional resources
│   └── secrets/          # Sensitive files (.env, keys)
├── temp/                 # Temporary files
│   └── app/
└── tmp/                  # Alternative temporary directory
    └── app/
```

## 🚀 Main File: `pon-server.js`

### Description

**Size**: 1071 lines  
**Purpose**: Main server that orchestrates all Pong game logic, room management, matchmaking and real-time communication.

### Main Features

#### 🎮 Game Server with Socket.IO

- **Rooms System**: Game rooms for PvP, vs AI, and tournaments
- **Game Loop**: Physics update at 60 FPS
- **Ball Physics**: Collisions, bounces, acceleration
- **Paddle Control**: Player movement synchronization
- **AI Opponents**: 4 difficulty levels (Easy, Medium, Hard, Expert)
- **Replay System**: Match recording and playback

#### 📊 Socket.IO Events

```javascript
// Connection and authentication
socket.on('connect', () => {...})
socket.on('disconnect', () => {...})

// Room management
socket.emit('createRoom', roomName, options)
socket.emit('joinRoom', roomId)
socket.emit('leaveRoom')
socket.on('roomsList')

// Gameplay
socket.emit('paddleMove', { y: number })
socket.emit('startGame')
socket.on('gameUpdate', (gameState) => {...})
socket.on('gameOver', (result) => {...})

// Tournaments
socket.emit('createTournament', players)
socket.on('tournamentUpdate', (bracket) => {...})
```

#### 🧠 Artificial Intelligence

```javascript
// AI algorithm excerpt (simplified)
function updateAIPaddle(difficulty, ballY, paddleY) {
  const target = predictBallPosition(ball);
  const error = calculateError(difficulty);
  const speed = getAISpeed(difficulty);
  
  if (paddleY < target - error) {
    return paddleY + speed;
  } else if (paddleY > target + error) {
    return paddleY - speed;
  }
  return paddleY;
}

// Difficulty levels
const difficulties = {
  easy: { speed: 3, error: 50, reaction: 200 },
  medium: { speed: 5, error: 20, reaction: 100 },
  hard: { speed: 7, error: 10, reaction: 50 },
  expert: { speed: 9, error: 2, reaction: 10 }
};
```

#### 📈 Game State Structure

```javascript
const gameState = {
  roomId: string,
  players: [
    { id: string, username: string, paddle: { y: number, height: number } },
    { id: string, username: string, paddle: { y: number, height: number } }
  ],
  ball: {
    x: number,
    y: number,
    vx: number,
    vy: number,
    radius: number
  },
  score: { player1: number, player2: number },
  status: 'waiting' | 'playing' | 'paused' | 'finished',
  timestamp: number
};
```

#### 🔄 Game Loop

```javascript
// Update every 16ms (60 FPS)
function gameLoop(roomId) {
  const room = rooms.get(roomId);
  
  // 1. Update ball position
  room.ball.x += room.ball.vx;
  room.ball.y += room.ball.vy;
  
  // 2. Wall collisions
  if (room.ball.y <= 0 || room.ball.y >= CANVAS_HEIGHT) {
    room.ball.vy *= -1;
  }
  
  // 3. Paddle collisions
  if (checkPaddleCollision(room.ball, room.players[0].paddle)) {
    room.ball.vx *= -1.05;  // Gradual acceleration
    room.ball.vy += calculateSpin(room.players[0].paddle);
  }
  
  // 4. Detect points
  if (room.ball.x <= 0) {
    room.score.player2++;
    resetBall(room);
  } else if (room.ball.x >= CANVAS_WIDTH) {
    room.score.player1++;
    resetBall(room);
  }
  
  // 5. Send update to clients
  io.to(roomId).emit('gameUpdate', room);
  
  // 6. Check end of game
  if (room.score.player1 >= 5 || room.score.player2 >= 5) {
    endGame(room);
  } else {
    setTimeout(() => gameLoop(roomId), 16);
  }
}
```

---

## 🔐 Authentication Module: `auth.js`

### Description

**Size**: 522 lines  
**Purpose**: Complete authentication management with JWT, OAuth 2.0, and bcrypt for passwords.

### REST Endpoints

```javascript
// User registration
POST /api/auth/register
Body: { username, email, password }
Response: { message: "User created", userId }

// Standard login
POST /api/auth/login
Body: { username, password }
Response: { token, refreshToken, user }

// OAuth login (Google, 42)
GET /api/auth/oauth/:provider
Redirect: OAuth provider authorization page
Callback: /api/auth/oauth/:provider/callback

// Verify token
GET /api/auth/verify
Headers: { Authorization: "Bearer <token>" }
Response: { valid: boolean, user }

// Refresh token
POST /api/auth/refresh
Body: { refreshToken }
Response: { token }

// Logout
POST /api/auth/logout
Headers: { Authorization: "Bearer <token>" }
Response: { message: "Logged out" }
```

### Authentication Flow

```
┌─────────────┐
│   Client    │
└──────┬──────┘
       │ POST /api/auth/login
       │ { username, password }
       ↓
┌─────────────────┐
│   auth.js       │
│  1. Find user   │
│  2. bcrypt.compare(password, hash)
│  3. Generate JWT token
│  4. Generate refresh token
└──────┬──────────┘
       │ { token, user }
       ↓
┌─────────────┐
│   Client    │
│ Saves token │
│ in localStorage
└─────────────┘
```

### Security

```javascript
// Password hashing with bcrypt
const bcrypt = require('bcrypt');
const saltRounds = 10;

// On registration
const hashedPassword = await bcrypt.hash(password, saltRounds);
await User.create({ username, email, password: hashedPassword });

// On login
const user = await User.findOne({ where: { username } });
const isValid = await bcrypt.compare(password, user.password);

if (!isValid) {
  return reply.code(401).send({ error: 'Invalid credentials' });
}
```

### JWT Tokens

```javascript
const jwt = require('jsonwebtoken');

// Generate token
const token = jwt.sign(
  { userId: user.id, username: user.username },
  process.env.JWT_SECRET,
  { expiresIn: '1h' }
);

// Refresh token (longer-lived)
const refreshToken = jwt.sign(
  { userId: user.id },
  process.env.JWT_REFRESH_SECRET,
  { expiresIn: '7d' }
);

// Authentication middleware
fastify.decorate('authenticate', async (request, reply) => {
  try {
    const token = request.headers.authorization?.split(' ')[1];
    const decoded = jwt.verify(token, process.env.JWT_SECRET);
    request.user = await User.findByPk(decoded.userId);
  } catch (error) {
    reply.code(401).send({ error: 'Invalid token' });
  }
});
```

---

## 💬 Chat Module: `chat.js`

### Description

**Size**: 376 lines  
**Purpose**: Complete instant messaging system with support for private conversations, groups, and user blocking.

### REST Endpoints

```javascript
// Conversations
GET    /api/conversations              // List user conversations
POST   /api/conversations              // Create new conversation
GET    /api/conversations/:id/messages // Get messages from a conversation
DELETE /api/conversations/:id          // Delete conversation

// Messages
POST   /api/messages                   // Send message
PUT    /api/messages/:id               // Edit message
DELETE /api/messages/:id               // Delete message

// Blocked users
GET    /api/blocked-users              // List blocked users
POST   /api/blocked-users/:userId      // Block user
DELETE /api/blocked-users/:userId      // Unblock user
```

### Socket.IO Events

```javascript
// Join chat room
socket.emit('join-chat', conversationId)

// Send message
socket.emit('send-message', {
  conversationId,
  text,
  attachments
})

// Receive message in real time
socket.on('new-message', (message) => {
  // Update UI with new message
})

// Typing indicator
socket.emit('typing', { conversationId })
socket.on('user-typing', ({ userId, username }) => {
  // Show "User is typing..."
})

// Message read
socket.emit('message-read', { messageId })
socket.on('message-read-receipt', ({ messageId, readBy }) => {
  // Mark message as read with double check
})
```

### Database Models

```javascript
// Conversation Model
const Conversation = sequelize.define('Conversation', {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  name: DataTypes.STRING,  // Group name (null for private)
  isGroup: { type: DataTypes.BOOLEAN, defaultValue: false },
  createdAt: DataTypes.DATE
});

// Message Model
const Message = sequelize.define('Message', {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  conversationId: DataTypes.INTEGER,
  senderId: DataTypes.INTEGER,
  text: DataTypes.TEXT,
  attachments: DataTypes.JSON,  // Attachment file URLs
  isEdited: { type: DataTypes.BOOLEAN, defaultValue: false },
  createdAt: DataTypes.DATE
});

// BlockedUser Model
const BlockedUser = sequelize.define('BlockedUser', {
  blockerId: DataTypes.INTEGER,  // Who blocks
  blockedId: DataTypes.INTEGER   // Who is blocked
});

// Relationships
Conversation.hasMany(Message, { foreignKey: 'conversationId' });
Message.belongsTo(User, { foreignKey: 'senderId' });
User.hasMany(BlockedUser, { foreignKey: 'blockerId' });
```

### Blocking Logic

```javascript
// Check if a user is blocked
async function isBlocked(userId, targetUserId) {
  const block = await BlockedUser.findOne({
    where: {
      [Op.or]: [
        { blockerId: userId, blockedId: targetUserId },
        { blockerId: targetUserId, blockedId: userId }
      ]
    }
  });
  return !!block;
}

// Filter messages from blocked users
app.get('/api/conversations/:id/messages', async (req, reply) => {
  const messages = await Message.findAll({
    where: { conversationId: req.params.id },
    include: [{ model: User, as: 'sender' }]
  });

  // Filter blocked users
  const blockedUsers = await BlockedUser.findAll({
    where: { blockerId: req.user.id }
  });
  const blockedIds = blockedUsers.map(b => b.blockedId);

  const filteredMessages = messages.filter(
    m => !blockedIds.includes(m.senderId)
  );

  return filteredMessages;
});
```

---

## 🗄️ Database: `db.js`

### Description

**Purpose**: Sequelize ORM configuration, model and relationship definitions.

### Configuration

```javascript
const { Sequelize, DataTypes } = require('sequelize');

// SQLite for development
const sequelize = new Sequelize({
  dialect: 'sqlite',
  storage: './srcs/secrets/app.db',
  logging: false  // Disable SQL logs in production
});

// Test connection
sequelize.authenticate()
  .then(() => console.log('Database connected'))
  .catch(err => console.error('Database connection error:', err));
```

### Main Models

```javascript
// User Model
const User = sequelize.define('User', {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  username: { type: DataTypes.STRING, unique: true, allowNull: false },
  email: { type: DataTypes.STRING, unique: true, allowNull: false },
  password: DataTypes.STRING,  // bcrypt hash
  displayName: DataTypes.STRING,
  avatar: DataTypes.STRING,    // Avatar URL
  bio: DataTypes.TEXT,
  oauthProvider: DataTypes.STRING,  // 'google', '42', null
  oauthId: DataTypes.STRING,
  wins: { type: DataTypes.INTEGER, defaultValue: 0 },
  losses: { type: DataTypes.INTEGER, defaultValue: 0 },
  elo: { type: DataTypes.INTEGER, defaultValue: 1000 },
  createdAt: DataTypes.DATE
});

// Match Model
const Match = sequelize.define('Match', {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  player1Id: DataTypes.INTEGER,
  player2Id: DataTypes.INTEGER,
  winnerId: DataTypes.INTEGER,
  scorePlayer1: DataTypes.INTEGER,
  scorePlayer2: DataTypes.INTEGER,
  duration: DataTypes.INTEGER,  // In seconds
  mode: DataTypes.STRING,       // 'PvP', 'AI', 'Tournament'
  replayData: DataTypes.JSON,   // Replay data
  createdAt: DataTypes.DATE
});

// FriendRequest Model
const FriendRequest = sequelize.define('FriendRequest', {
  senderId: DataTypes.INTEGER,
  receiverId: DataTypes.INTEGER,
  status: {
    type: DataTypes.ENUM('pending', 'accepted', 'rejected'),
    defaultValue: 'pending'
  },
  createdAt: DataTypes.DATE
});

// Friendship Model (auto-generated when FriendRequest is accepted)
const Friendship = sequelize.define('Friendship', {
  user1Id: DataTypes.INTEGER,
  user2Id: DataTypes.INTEGER,
  createdAt: DataTypes.DATE
});
```

### Relationships

```javascript
// User → Matches
User.hasMany(Match, { as: 'matchesAsPlayer1', foreignKey: 'player1Id' });
User.hasMany(Match, { as: 'matchesAsPlayer2', foreignKey: 'player2Id' });
Match.belongsTo(User, { as: 'player1', foreignKey: 'player1Id' });
Match.belongsTo(User, { as: 'player2', foreignKey: 'player2Id' });

// User → Friend requests
User.hasMany(FriendRequest, { as: 'sentRequests', foreignKey: 'senderId' });
User.hasMany(FriendRequest, { as: 'receivedRequests', foreignKey: 'receiverId' });

// Friendship (many-to-many)
User.belongsToMany(User, { as: 'friends', through: Friendship, foreignKey: 'user1Id' });
```

### Synchronization

```javascript
// Create tables if they don't exist
sequelize.sync({ force: false })  // force: true → DROP + CREATE
  .then(() => console.log('Database tables created'))
  .catch(err => console.error('Sync error:', err));
```

---

## 📦 Dependencies (`package.json`)

```json
{
  "name": "transcendence-backend",
  "version": "1.0.0",
  "scripts": {
    "start": "node index.js",
    "dev": "nodemon index.js",
    "test": "jest",
    "migrate": "sequelize-cli db:migrate"
  },
  "dependencies": {
    "fastify": "^4.25.0",
    "socket.io": "^4.7.0",
    "sequelize": "^6.32.0",
    "sqlite3": "^5.1.6",
    "bcrypt": "^5.1.1",
    "jsonwebtoken": "^9.0.2",
    "dotenv": "^16.3.1",
    "cors": "^2.8.5"
  },
  "devDependencies": {
    "nodemon": "^3.0.1",
    "jest": "^29.6.0"
  }
}
```

## 🐳 Dockerfile

```dockerfile
FROM node:20-alpine

WORKDIR /app

# Copy package files
COPY package*.json ./

# Install dependencies
RUN npm ci --only=production

# Copy source code
COPY . .

# Expose port
EXPOSE 3000

# Start command
CMD ["node", "index.js"]
```

## 🔗 Frontend Integration

```typescript
// Frontend → Backend (REST)
const response = await fetch('http://localhost:3000/api/users/me', {
  headers: { Authorization: `Bearer ${token}` }
});

// Frontend → Backend (Socket.IO)
import { io } from 'socket.io-client';

const socket = io('http://localhost:3000', {
  auth: { token: localStorage.getItem('auth_token') }
});

socket.on('connect', () => {
  console.log('Connected to game server');
});

socket.emit('createRoom', 'My Room', { mode: 'AI', difficulty: 'hard' });
```

## 🚀 Running the Server

```bash
# Development with auto-reload
npm run dev

# Production
npm start

# Docker
docker build -t transcendence-backend .
docker run -p 3000:3000 transcendence-backend
```

---

**Location**: `/backend/`  
**Technologies**: Node.js 20, Fastify 4, Socket.IO 4, Sequelize 6, SQLite 3, bcrypt, JWT  
