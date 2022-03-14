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
        - Insert is pretty fast
        - Right now, deletion is ultra slow, need to delete it in O(1)
          - store QTreeNodes inside collider and Delete+Insert when dirty?
    - [x] What to actually store inside QTreeNode?
      - Pointer to IColliderComponent?
    - [ ] Query
- [ ] RigidBodyComponent
  - [x] Flag GameObject (or just the rigidbody itself) dirty upon movement
      - flagging collider component upon transform change
  - [ ] Static RigidBody flag (f.e. walls - they will never move, so no need to update/check)

### Problems to solve

- [x] Registering colliders into PhysicsSubsystem inside Base class constructor won't work
  - Added OnCreate event that gets called upon AddComponent (first thing after make_unique<>)
- [x] When to initialize QuadTree inside PhysicsSubsystem
  - First time a collider tries to get inserted into QTree - create it

​	