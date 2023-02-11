# Dungeons Survival

![image](https://user-images.githubusercontent.com/9076709/213876773-cdfe19d5-2408-473a-bb7f-fa2528609da3.png)

## Fixes I want to do but will probably forget about:
- **Engine/Game** messageTypes - right now we only support Engine message types and game needs to add theirs into this enum. Ugly
- **Enemy scatter** - currently the enemy holds a field that registers nearby enemies and spawns new bullets upon death. Maybe it would be better for bullet itself to spawn new bullet, so it's possible to propagate bullet stats and settings.
- **Health bars above enemies** - simple shape above an Actor?
- **Reload bar for player**	- bar animation right above player object? Still the same issue as with the enemy health bars
