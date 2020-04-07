Level0 = {
    assets = {
        [0] = { type="texture", id = "terrain-texture", file = "./assets/tilemaps/tilemap.png" },
        [1] = { type="texture", id = "player-texture", file = "./assets/images/spritesheet.png" },
        [2] = { type="texture", id = "tank-big-right-texture", file = "./assets/images/tank-big-right.png" },
        [3] = { type="texture", id = "tank-big-down-texture", file = "./assets/images/tank-big-down.png" },
        [4] = { type="texture", id = "projectile-texture", file = "./assets/images/bullet-enemy.png" },
        [5] = { type="font", id = "charriot-font", file = "./assets/fonts/charriot.ttf", fontSize = 14 },
        [6] = { type="sound", id = "background-music", file = "./assets/sounds/videogames.mp3" }
    },
    map = {
        textureAssetID = "terrain-texture",
        file = "./assets/tilemaps/testmap.map",
        scale = 2,
        tileSize = 16,
        mapSizeX = 25,
        mapSizeY = 30
    },
    entities = {
        [0] = {
            name = "player",
            layer = 4,
            components = {
                transform = {
                    position = {
                        x = 240,
                        y = 106
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 48,
                    height = 48,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetID = "player-texture",
                    animated = true,
                    frameCount = 6,
                    animationSpeed = 90,
                    hasDirections = true,
                    fixed = false
                },
                collider = {
                    tag = "PLAYER"
                },
                input = {
                    keyboard = {
                        up = "w",
                        left = "a",
                        down = "s",
                        right = "d",
                        shoot = "space"
                    }
                },
                audio = {
                    musicID = "background-music"
				}
            }
        },
        [1] = {
            name = "tank1",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 300,
                        y = 100
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetID = "tank-big-right-texture",
                    animated = false
                },
                collider = {
                    tag = "ENEMY"
                },
                projectileEmitter = {
                    speed = 70,
                    range = 300,
                    angle = 0,
                    width = 4,
                    height = 4,
                    shouldLoop = true,
                    textureAssetID = "projectile-texture"
                }
            }
        },
        [2] = {
            name = "tank2",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 660,
                        y = 535
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetID = "tank-big-down-texture",
                    animated = false
                },
                collider = {
                    tag = "ENEMY"
                },
                projectileEmitter = {
                    speed = 70,
                    range = 300,
                    angle = 90,
                    width = 4,
                    height = 4,
                    shouldLoop = true,
                    textureAssetID = "projectile-texture"
                }
            }
        }
    }
}
