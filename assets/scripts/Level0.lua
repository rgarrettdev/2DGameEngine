Level0 = {
    assets = {
        [0] = { type="texture", id = "terrain-texture", file = "./assets/tilemaps/tilemap.png" },
        [1] = { type="texture", id = "player-texture", file = "./assets/images/spritesheet.png" },
        [2] = { type="texture", id = "tank-big-right-texture", file = "./assets/images/tank-big-right.png" },
        [3] = { type="texture", id = "tank-big-down-texture", file = "./assets/images/tank-big-down.png" },
        [4] = { type="font", id = "charriot-font", file = "./assets/fonts/charriot.ttf", fontSize = 14 }
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
                    textureAssetId = "player-texture",
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
                }
            }
        },
        [1] = {
            name = "tank1",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 650,
                        y = 405
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
                    textureAssetId = "tank-big-left-texture",
                    animated = false
                },
                collider = {
                    tag = "ENEMY"
                },
                projectileEmitter = {
                    speed = 70,
                    range = 300,
                    angle = 180,
                    width = 4,
                    height = 4,
                    shouldLoop = true,
                    textureAssetId = "projectile-texture"
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
                    textureAssetId = "tank-big-down-texture",
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
                    textureAssetId = "projectile-texture"
                }
            }
        }
    }
}
