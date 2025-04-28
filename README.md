# 🖥️ MidWare

An advanced cheat for **Rainbow Six Siege**, specifically designed for the **November 17th Shadow Legacy** build.

This project is split into two components:

- **External Loader**  
  Responsible for DLL injection and applying external-only features that are blocked internally.
- **Internal DLL**  
  Hosts the main CLI menu and all internal memory modifications.

The CLI shows the current status of all toggles (ON/OFF) and updates live as hotkeys are pressed.

---

## 🔧 Features

| Keybind      | Feature                 | Description                                                                                   |
|:-------------|-------------------------|-----------------------------------------------------------------------------------------------|
| **MISC**     |                         |                                                                                               |
| [N/A]        | Unlock All              | Automatically unlocks all skins, attachment skins, headgears, and uniforms.                   |
| [NUM0]       | Uninject                | Safely removes the DLL and instructs the loader to terminate the executable.                  |
| **WEAPON**   |                         |                                                                                               |
| [NUM1]       | Infinite Ammo           | Never run out of bullets — keeps your clip perpetually full.                                  |
| [NUM2]       | Rapid Fire              | Removes fire rate cap and makes all weapons fully-automatic.                                  |
| [NUM3]       | No Recoil               | Removes weapon recoil for pinpoint accuracy.                                                  |
| [NUM4]       | No Spread               | Removes hipfire spread for accurate run-and-gun.                                              |
| [NUM5]       | InstaKill               | Makes every bullet lethal — 1 shot, 1 kill.                                                   |
| [NUM6]       | Run and Shoot           | Allows sprinting in any direction, while crouched, or while firing.                           |
| [NUM7]       | Gun Caliber             | Alters weapon caliber to Skeleton Key, CSRX 300, DP27, or Mav's Torch.                        |
| [NUM8]       | Bolt Script             | Removes pump or bolt action animations for instant follow-up shots.                           |
| [NUM9]       | Knife Reach             | Dramatically extends melee range.                                                             |
| **PLAYER**   |                         |                                                                                               |
| [F1]         | GodMode                 | Prevents the player from taking damage.                                                       |
| [F2]         | Player Speed            | Greatly increases player movement speed.                                                      |
| [F3]         | NoClip                  | Walk through walls and objects without collision.                                             |
| [F4]         | Infinite Gadgets        | Never run out of throwable gadgets.                                                           |
| **VISUAL**   |                         |                                                                                               |
| [F5]         | Glow ESP                | Highlights enemies through walls and smoke.                                                   |
| [F6]         | Fisheye FOV             | Modifies FOV for a panoramic fisheye effect.                                                  |
| [F7]         | Remove Sky              | Removes the current skybox.                                                                   |
| [F8]         | Third Person            | Allows third-person camera view.                                                              |
| **DRONE**    |                         |                                                                                               |
| [F9]         | No Gravity              | Removes gravity from drones.                                                                  |
| [F10]        | Drone Speed             | Greatly increases drone movement speed.                                                       |
| [F11]        | Twitch / Echo Buff      | Infinite ammo, range, and rapid fire for Twitch / Echo drones.                                |
| **T-HUNT**   |                         |                                                                                               |
| [PGUP]       | Lock Wave               | Locks the current wave at Wave 0, allowing infinite enemy waves without end.                  |
| [PGDN]       | Can Go Outside          | Prevents death when outside longer than 10 seconds.                                           |

---

## 📦 Setup Instructions

1. Compile both the **internal DLL** and the **external loader**, or get them from the Release tab.
2. Launch the loader (`MidWare.exe`) which will:
   - Inject the internal DLL into `RainbowSix.exe`.
   - Initialize shared memory for feature toggles.
3. Use hotkeys in-game to enable/disable features.
4. Exit cleanly using `[NUM0]` or by closing the game.

---

## 📺 Showcase

![Menu Showcase](image.png)

---
