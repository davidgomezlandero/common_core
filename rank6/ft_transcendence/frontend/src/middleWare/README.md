# 🛡️ MiddleWare - Protected Routes Middleware

## 📋 General Overview

This directory contains **middlewares** for React Router that protect private routes, validate authentication and manage redirections. They implement the **Higher-Order Component (HOC)** or **wrapper components** pattern to encapsulate authorization logic.

## 🗂️ Structure

### `middleWare.tsx` - Main Middleware

**Purpose**: Protect routes that require verified authentication.

## 🔐 Middleware Implementation

### ProtectedRoute Component

```typescript
// middleWare.tsx
import { Navigate, useLocation } from 'react-router-dom';
import { useAuth } from '../Context/AuthContext';

interface ProtectedRouteProps {
  children: React.ReactNode;
  redirectTo?: string;
  requiredRole?: 'user' | 'admin';
}

export function ProtectedRoute({ 
  children, 
  redirectTo = '/login',
  requiredRole 
}: ProtectedRouteProps) {
  const { isAuthenticated, user, loading } = useAuth();
  const location = useLocation();

  // Show loader while verifying token
  if (loading) {
    return (
      <div className="flex items-center justify-center h-screen">
        <div className="animate-spin rounded-full h-32 w-32 border-t-2 border-b-2 border-blue-500"></div>
      </div>
    );
  }

  // Redirect to login if not authenticated
  if (!isAuthenticated) {
    // Save the attempted route for post-login redirect
    return <Navigate to={redirectTo} state={{ from: location }} replace />;
  }

  // Verify role if required
  if (requiredRole && user?.role !== requiredRole) {
    return <Navigate to="/unauthorized" replace />;
  }

  // Authenticated user → render children
  return <>{children}</>;
}
```

### Variant: RequireAuth HOC

```typescript
// Alternative HOC pattern
export function requireAuth<P extends object>(
  Component: React.ComponentType<P>
) {
  return function ProtectedComponent(props: P) {
    const { isAuthenticated, loading } = useAuth();

    if (loading) return <LoadingSpinner />;
    if (!isAuthenticated) return <Navigate to="/login" />;

    return <Component {...props} />;
  };
}

// Usage
const ProtectedProfile = requireAuth(Profile);
```

## 🎯 Usage in Routes

### React Router Configuration

```typescript
// App.tsx
import { createBrowserRouter, RouterProvider } from 'react-router-dom';
import { ProtectedRoute } from './middleWare/middleWare';

const router = createBrowserRouter([
  {
    path: '/login',
    element: <Login />
  },
  {
    path: '/',
    element: (
      <ProtectedRoute>
        <Layout />  {/* Layout with sidebar + outlet */}
      </ProtectedRoute>
    ),
    children: [
      {
        index: true,
        element: <Index />  // Dashboard
      },
      {
        path: 'game',
        element: <Game />
      },
      {
        path: 'tournament',
        element: <Tournamenst />
      },
      {
        path: 'profile/:userId?',
        element: <Profile />
      },
      {
        path: 'matches',
        element: <Matches />
      },
      {
        path: 'friends',
        element: <FriendsRequest />
      },
      {
        path: 'chat',
        element: <Chat />
      },
      {
        path: 'settings',
        element: (
          <ProtectedRoute requiredRole="admin">
            <Settings />
          </ProtectedRoute>
        )
      }
    ]
  },
  {
    path: '/unauthorized',
    element: <Unauthorized />
  },
  {
    path: '*',
    element: <NotFound />
  }
]);

function App() {
  return (
    <AuthProvider>
      <ComponentsProvider>
        <RouterProvider router={router} />
      </ComponentsProvider>
    </AuthProvider>
  );
}
```

### Post-Login Redirect

```typescript
// Login.tsx
import { useAuth } from '../Context/AuthContext';
import { useNavigate, useLocation } from 'react-router-dom';

function Login() {
  const { login } = useAuth();
  const navigate = useNavigate();
  const location = useLocation();

  const handleLogin = async (credentials: LoginCredentials) => {
    await login(credentials);
    
    // Redirect to the originally attempted route
    const from = location.state?.from?.pathname || '/';
    navigate(from, { replace: true });
  };

  return <form onSubmit={handleLogin}>...</form>;
}
```

## 🔒 Security Validations

### 1. Token Expiration Check

```typescript
// middleWare.tsx
export function ProtectedRoute({ children }: ProtectedRouteProps) {
  const { token, logout } = useAuth();

  useEffect(() => {
    if (token) {
      const decoded = jwtDecode<JWTPayload>(token);
      const expiresIn = (decoded.exp * 1000) - Date.now();

      if (expiresIn < 0) {
        // Expired token
        logout();
        return;
      }

      // Auto-logout before expiration
      const timeoutId = setTimeout(() => {
        alert('Your session has expired');
        logout();
      }, expiresIn);

      return () => clearTimeout(timeoutId);
    }
  }, [token]);

  // ... rest of the code
}
```

### 2. Network Status Handling

```typescript
// middleWare.tsx
function ProtectedRoute({ children }: ProtectedRouteProps) {
  const [isOnline, setIsOnline] = useState(navigator.onLine);

  useEffect(() => {
    const handleOnline = () => setIsOnline(true);
    const handleOffline = () => setIsOnline(false);

    window.addEventListener('online', handleOnline);
    window.addEventListener('offline', handleOffline);

    return () => {
      window.removeEventListener('online', handleOnline);
      window.removeEventListener('offline', handleOffline);
    };
  }, []);

  if (!isOnline) {
    return (
      <div className="flex items-center justify-center h-screen">
        <div className="text-center">
          <h2>No Internet Connection</h2>
          <p>Check your connection and reload the page</p>
        </div>
      </div>
    );
  }

  // ... rest of the validations
}
```

### 3. Frontend Rate Limiting

```typescript
// middleWare.tsx
const requestCounts = new Map<string, number>();

export function RateLimitedRoute({ 
  children, 
  maxRequests = 100, 
  windowMs = 60000 
}: RateLimitedRouteProps) {
  const { user } = useAuth();
  const [blocked, setBlocked] = useState(false);

  useEffect(() => {
    if (!user) return;

    const key = `rate_limit_${user.id}`;
    const count = requestCounts.get(key) || 0;

    if (count >= maxRequests) {
      setBlocked(true);
      setTimeout(() => {
        requestCounts.delete(key);
        setBlocked(false);
      }, windowMs);
    } else {
      requestCounts.set(key, count + 1);
    }
  }, [user]);

  if (blocked) {
    return <div>Too many requests. Please try again in a few minutes.</div>;
  }

  return <>{children}</>;
}
```

## 📊 Authentication Flow

```
User visits /game
    ↓
<ProtectedRoute> intercepts
    ↓
loading? → Show spinner
    ↓
isAuthenticated? 
    ├─ NO → <Navigate to="/login" state={{ from: '/game' }} />
    │           ↓
    │       User enters credentials
    │           ↓
    │       login() successful
    │           ↓
    │       navigate(location.state.from) → /game
    │
    └─ YES → requiredRole?
              ├─ NO → Render children (<Game />)
              └─ YES → user.role === requiredRole?
                        ├─ YES → Render children
                        └─ NO → <Navigate to="/unauthorized" />
```

## 🎨 Auxiliary UI Components

### LoadingSpinner

```typescript
// LoadingSpinner.tsx
export function LoadingSpinner() {
  return (
    <div className="flex items-center justify-center h-screen bg-gray-900">
      <div className="relative">
        <div className="animate-spin rounded-full h-32 w-32 border-t-4 border-b-4 border-blue-500"></div>
        <div className="absolute top-1/2 left-1/2 transform -translate-x-1/2 -translate-y-1/2">
          <span className="text-white text-xl font-bold">Loading...</span>
        </div>
      </div>
    </div>
  );
}
```

### Unauthorized Page

```typescript
// Unauthorized.tsx
export function Unauthorized() {
  const navigate = useNavigate();

  return (
    <div className="flex flex-col items-center justify-center h-screen">
      <h1 className="text-6xl font-bold text-red-500">403</h1>
      <p className="text-2xl mt-4">You do not have permission to access this page</p>
      <button 
        onClick={() => navigate('/')}
        className="mt-8 px-6 py-3 bg-blue-500 text-white rounded hover:bg-blue-600"
      >
        Back to home
      </button>
    </div>
  );
}
```

## 🔗 Backend Integration

### Token Validation in Backend

```javascript
// backend/auth.js (Fastify middleware)
fastify.decorate('authenticate', async (request, reply) => {
  try {
    const token = request.headers.authorization?.split(' ')[1];
    
    if (!token) {
      return reply.code(401).send({ error: 'Token not provided' });
    }

    const decoded = jwt.verify(token, process.env.JWT_SECRET);
    request.user = await User.findByPk(decoded.userId);

    if (!request.user) {
      return reply.code(401).send({ error: 'User not found' });
    }
  } catch (error) {
    return reply.code(401).send({ error: 'Invalid token' });
  }
});

// Usage in routes
fastify.get('/api/profile', {
  preHandler: [fastify.authenticate]
}, async (request, reply) => {
  return { user: request.user };
});
```

## 🧪 Testing

### ProtectedRoute Test

```typescript
// middleWare.test.tsx
import { render, screen } from '@testing-library/react';
import { MemoryRouter } from 'react-router-dom';
import { AuthProvider } from '../Context/AuthContext';
import { ProtectedRoute } from './middleWare';

describe('ProtectedRoute', () => {
  it('should redirect to login when not authenticated', () => {
    // Mock AuthContext with isAuthenticated = false
    render(
      <MemoryRouter initialEntries={['/protected']}>
        <AuthProvider>
          <ProtectedRoute>
            <div>Protected Content</div>
          </ProtectedRoute>
        </AuthProvider>
      </MemoryRouter>
    );

    expect(screen.queryByText('Protected Content')).not.toBeInTheDocument();
  });

  it('should render children when authenticated', () => {
    // Mock AuthContext with isAuthenticated = true
    render(
      <MemoryRouter initialEntries={['/protected']}>
        <AuthProvider>
          <ProtectedRoute>
            <div>Protected Content</div>
          </ProtectedRoute>
        </AuthProvider>
      </MemoryRouter>
    );

    expect(screen.getByText('Protected Content')).toBeInTheDocument();
  });
});
```

## 🚀 Future Improvements

### 1. Session Management

```typescript
// Implement automatic refresh token
const refreshToken = async () => {
  const response = await fetch('/api/auth/refresh', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ refreshToken: localStorage.getItem('refresh_token') })
  });
  
  const { token } = await response.json();
  localStorage.setItem('auth_token', token);
  return token;
};
```

### 2. Biometric Authentication

```typescript
// WebAuthn API for biometric login
if (window.PublicKeyCredential) {
  const credential = await navigator.credentials.create({
    publicKey: {
      challenge: new Uint8Array(32),
      rp: { name: "Transcendence" },
      user: {
        id: new Uint8Array(16),
        name: user.email,
        displayName: user.username
      },
      pubKeyCredParams: [{ alg: -7, type: "public-key" }]
    }
  });
}
```

### 3. Multi-Factor Authentication

```typescript
// 2FA code verification
export function TwoFactorRoute({ children }: { children: React.ReactNode }) {
  const { user } = useAuth();
  const [verified, setVerified] = useState(false);

  if (user?.has2FA && !verified) {
    return <TwoFactorModal onVerify={() => setVerified(true)} />;
  }

  return <>{children}</>;
}
```

---

**Location**: `/frontend/src/middleWare/`  
**Technologies**: React Router v7, React Context API, JWT Decode  
**Related documentation**:
- `../Context/AuthContext.tsx` - Authentication provider
- `/backend/auth.js` - Server authentication middleware
- `../App.tsx` - Route configuration