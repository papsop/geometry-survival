# Dungeons Survival

![image](https://user-images.githubusercontent.com/9076709/213876773-cdfe19d5-2408-473a-bb7f-fa2528609da3.png)

## Fixes I want to do but will probably forget about:
- Nicer enemy stunning, right now it checks for Category bits on the collision that happened inside `AIChasePlayerComponent`. It should probably listen to Actor taking damage and responding with a stun+knockback instead of listening to physics collision itself.
- Combat text - damage numbers from actors. I tried implementing it via TGUI library to be a part of UI itself, but working with WorldSpace in UI library is kinda meh. Let's just implement it via SFML and spawn these labels in a world.
