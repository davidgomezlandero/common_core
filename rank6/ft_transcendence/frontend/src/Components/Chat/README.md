# 💬 Chat - Messaging Interface Components

## 📋 General Overview

This directory contains the specialized React components that make up the complete real-time chat system of the application. It implements a modern instant messaging interface with support for private conversations, user blocking, and contact management.

## 🗂️ Component Structure

### Main Components

#### `ChatMain.tsx`
**Purpose**: Main container component that orchestrates the entire chat interface.

**Responsibilities**:
- Manages the two-panel layout (sidebar + message area)
- Coordinates communication between subcomponents
- Maintains the global state of the active chat
- Handles conversation selection

**Project relation**: Main entry point invoked from `Chat.tsx` in the parent directory.

---

#### `ChatSideBar.tsx`
**Purpose**: Left side panel with the list of active conversations.

**Features**:
- Displays all user conversations
- Shows unread message badges
- Allows searching/filtering conversations
- Button to start new conversations

**Communication**: Connects to the backend via Socket.IO for real-time updates.

---

#### `ConversationList.tsx`
**Purpose**: Renders the scrollable list of conversations in the sidebar.

**Characteristics**:
- Shows avatar, name and last message of each conversation
- Highlights the currently selected conversation
- Relative timestamp formatting ("5 min ago", "yesterday")
- Online/offline status indicators

**Data**: Consumes the conversations array from `ComponentsContext`.

---

### Messaging Components

#### `MessagesList.tsx`
**Purpose**: Main area displaying the message history of the selected conversation.

**Implementation**:
- Auto-scroll on receiving new messages
- "Bubble" design with alignment by sender (left/right)
- Lazy loading of older messages when scrolling up
- Timestamps and read confirmations

**Optimization**: List virtualization for efficient handling of thousands of messages.

---

#### `MessageInput.tsx`
**Purpose**: Input field for composing and sending messages.

**Features**:
- Textarea with auto-expansion while typing
- Send button and Enter key support (Shift+Enter for line break)
- "Typing..." indicator emitted to other users
- Attachment preview (if implemented)

**Validation**: Prevents sending empty or excessively long messages.

---

### Management Components

#### `ChatHeader.tsx`
**Purpose**: Top bar of the active conversation.

**Displays**:
- Avatar and name of the user being chatted with
- Connection status (online/offline/typing)
- Action buttons: profile, block, options

**Navigation**: Allows accessing the other user's profile via `ShowProfile.tsx`.

---

#### `NewChat.tsx`
**Purpose**: Modal/Panel to start a new conversation.

**Process**:
1. Shows list of available users (friends, acquaintances)
2. Search field by username
3. On selection, creates conversation and redirects to it

**API**: Calls `POST /api/conversations/create` with `otherUserId`.

---

#### `ShowProfile.tsx`
**Purpose**: Modal displaying the summary profile of the user being chatted with.

**Visible Information**:
- Avatar, username, displayName
- Game statistics (wins, losses)
- Button to view full profile
- Option to block/unblock

**Integration**: Shares logic with `Profile.tsx` in the parent directory.

---

### Security Components

#### `BlockUser.tsx`
**Purpose**: Interface to block a specific user.

**Flow**:
1. Confirmation via modal/dialog
2. API call `POST /api/block`
3. Immediate local state update
4. Hides the conversation from the sidebar

**Effect**: The blocked user cannot send messages or view the profile.

---

#### `BlockedUsersList.tsx`
**Purpose**: Management panel for blocked users.

**Features**:
- Complete list of blocked users
- "Unblock" button for each entry
- Search/filtering of the list
- Access from Settings or from the chat

**API**: Consumes `GET /api/blocked-users` and `DELETE /api/blocked-users/:id`.

---

## 🔄 Data Flow

```
Backend (chat.js)
    ↕️ Socket.IO (events: message, typing, read)
ComponentsContext.tsx (global state)
    ↕️
ChatMain.tsx (orchestrator)
    ├─→ ChatSideBar.tsx
    │       ├─→ ConversationList.tsx
    │       └─→ NewChat.tsx
    ├─→ ChatHeader.tsx
    │       └─→ ShowProfile.tsx
    ├─→ MessagesList.tsx
    └─→ MessageInput.tsx
```

## 🎨 Technologies and Patterns

- **React Hooks**: `useState`, `useEffect`, `useContext`, `useRef`
- **Context API**: Consumes `AuthContext` and `ComponentsContext`
- **Socket.IO Client**: For real-time messaging
- **TailwindCSS**: Styling via utility-first classes
- **TypeScript**: Strict typing via interfaces from `types.tsx`

## 🔗 Backend Integration

### REST Endpoints Used

```typescript
POST   /api/conversations/create     // Create conversation
GET    /api/conversations            // List conversations
GET    /api/messages/:conversationId // Get messages
POST   /api/messages                 // Send message (REST fallback)
POST   /api/block                    // Block user
GET    /api/blocked-users            // List blocked users
DELETE /api/blocked-users/:userId    // Unblock
```

### Socket.IO Events

```typescript
// Emitted by client
socket.emit('join-chat', conversationId)
socket.emit('send-message', { conversationId, text })
socket.emit('typing', { conversationId, isTyping })
socket.emit('read-messages', conversationId)

// Listened by client
socket.on('new-message', (message) => {...})
socket.on('user-typing', ({ userId, isTyping }) => {...})
socket.on('messages-read', ({ conversationId, readBy }) => {...})
```

## 📦 External Dependencies

- `socket.io-client`: Bidirectional WebSocket connection
- `react-icons`: Iconography (messages, notifications)
- `date-fns` or `dayjs`: Timestamp formatting (if used)

## 🧪 Testing and Validation

To test these components:

```bash
# 1. Ensure backend is running
cd backend && npm start

# 2. Login with two different users in separate browsers
# 3. User A starts a conversation with User B
# 4. Send messages bilaterally
# 5. Test blocking and verify chat is disabled
# 6. Unblock and verify restoration
```

## 🛡️ Security

- **Input validation**: Text sanitization to prevent XSS
- **Authentication required**: All endpoints verify JWT token
- **Bidirectional blocking**: Blocked user cannot interact
- **Rate limiting**: Backend prevents message spam

## 🚀 Future Improvements

- [ ] Support for multimedia messages (images, GIFs)
- [ ] Message reactions (emojis)
- [ ] Audio/video call messages
- [ ] End-to-end encryption
- [ ] Group chat rooms
- [ ] Reply to specific messages (threading)

---

**Location**: `/frontend/src/Components/Chat/`  
**Related documentation**: See `Chat.tsx` (parent), `chat.js` (backend), `ComponentsContext.tsx`