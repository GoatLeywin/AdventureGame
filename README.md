# Modular Text Adventure System

A **modular**, **expandable** system for creating text-based adventure games using simple room files and structured logic in C++.  
> ⚡ **Note:** This is a **framework**, not a finished game.

## Features

- 📜 **Room loading** from external `.txt` files
- 🗺️ **Coordinate-based world layout** (X and Y positions for rooms)
- 🧩 **Usable items** with programmable effects (e.g., unlock doors, reveal hidden items)
- 🚪 **Door locking/unlocking system** based on item use
- 🏗️ **Easily expandable** — just add new room files
- 🛠️ **Simple inventory and item management**

## How It Works

- Each **room** is a `.txt` file containing:
  - A **description**
  - A list of **items** found in the room
  - A list of **exits** (directions the player can travel)
  - A list of **usable items** and their **effects** (such as unlocking doors or revealing new items)

- The **player** can:
  - **Take** items
  - **Use** items (some cause effects in rooms)
  - **Move** between rooms if an exit exists

- **Movement** is blocked if the player tries to go in a direction not listed in the room's exits.

## Example Room File

```plaintext
description: You are in a dusty library. A locked door lies to the west and an open archway lies to the east.
items: torch, book
exits: east
usable_items:
torch: The torch lights up the dark corner, revealing a golden key! -> add_item:golden key
golden key: You unlock the western door! -> unlock_direction:west
