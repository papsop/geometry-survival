# Dungeons & Geometry

![image](https://user-images.githubusercontent.com/9076709/155303636-18c13151-962f-4707-a7a1-2107b92c55e2.png)

- Copy SFML dlls and `arial.ttf` from `\copy-to-bin\` to `\bin\Win64\Debug`

## Currently working on

- [ ]  Collision detection
  - [ ] Component collider data
    - [x] CircleCollider
    - [ ] AABB
  - [ ] QuadTree
    - [x] Basic splitting
    - [x] DebugDraw
    - [ ] Dynamic insert/update/delete
    - [ ] What to actually store inside QTreeNode?
      - Pointer to IColliderComponent?
    - [ ] Query
- [ ] RigidBodyComponent
  - [ ] Flag GameObject (or just the rigidbody itself) dirty upon movement
  - [ ] Static RigidBody flag (f.e. walls - they will never move, so no need to update/check)

### Problems to solve

- [ ] Registering colliders into PhysicsSubsystem inside Base class constructor won't work
  - The CircleColliderComponent itself isn't yet initialized - can't ask for ColliderData at the time of component registering
  - Maybe PhysicsSubsystem should store registered components outside of the QuadTree
    - [ ] during update check every component for movement (dirty flag) and update QuadTree
- [ ] When to initialize QuadTree inside PhysicsSubsystem
  - First time a collider registers into PhysicsSubsystem?

​	