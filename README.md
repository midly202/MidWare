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

| Keybind | Feature            | Description                                                                                   |
|--------:|--------------------|-----------------------------------------------------------------------------------------------|
|   [N/A] | Unlock All         | Automatically unlocks all skins, attachment skins, headgears, and uniforms.                   |
|   [0]   | Uninject           | Safely removes the DLL and instructs the loader to terminate the executable.                  |
|   [1]   | Infinite Ammo      | Never run out of bullets — keeps your clip perpetually full.                                  |
|   [2]   | Rapid Fire         | Removes fire rate cap and makes all weapons fully-automatic.                                  |
|   [3]   | No Recoil          | Removes weapon recoil for pinpoint accuracy.                                                  |
|   [4]   | No Spread          | Removes hipfire spread for accurate run-and-gun.                                              |
|   [5]   | InstaKill          | Makes every bullet lethal — 1 shot, 1 kill.                                                   |
|   [6]   | Speedy Gonzales    | Greatly increases player movement speed.                                                      |
|   [7]   | Fisheye FOV        | Modifies player and weapon FOV for a panoramic fisheye effect.                                |
|   [8]   | Remove Sky         | Removes the current skybox.                                                                   |
|   [9]   | Gun Caliber        | Alters current weapon's caliber to Skeleton Key, CSRX 300, DP27, or Mav's Torch.              |
|   [F1]  | Glow ESP           | Highlights enemies through walls and smoke.                                                   |
|   [F2]  | Run and Shoot      | Allows sprinting in any direction, while crouched, or while firing.                           |
|   [F3]  | Bolt Script        | Eliminates bolt or pump delays on applicable weapons.                                         |
|   [F4]  | Infinite Gadgets   | Never run out of throwable gadgets.                                                           |
|   [F5]  | Can Go Outside     | Prevents you from dying when outside for longer than 10 seconds in Protect Hostage.           |

test change cos git is stupid as fuck
---

## 📦 Setup Instructions

1. Compile both the **internal DLL** and the **external loader**.
2. Launch the loader (`MidWare.exe`) which will:
   - Inject the internal DLL into `RainbowSix.exe`.
   - Initialize shared memory for feature toggles.
3. Use hotkeys in-game to enable/disable features.
4. Exit cleanly using `[NUMPAD 0]` or by closing the game.

---
