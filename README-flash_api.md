# Libesphttpd Flash-API

The flash API is specified in RAML.  (see https://raml.org)
```yaml
#%RAML 1.0
title: flash
version: v1
baseUri: http://me.local/flash


/flashinfo.json:
    description: info about the partition table
    get:
        description: Returns a JSON of info about the partition table
        queryParameters:
            type:
                displayName: Partition Type
                type: string
                description: String name of partition type (app, data).  If not specified, return both app and data partitions.
                example: app
                required: false
        responses:
            200:
                body:
                    application/json:
                      type: object
                      properties:
                        app: array
                        data: array
                      example: |
                        {
                            "app":	[{
                                    "name":	"factory",
                                    "size":	4259840,
                                    "version":	"",
                                    "ota":	false,
                                    "valid":	true,
                                    "running":	false,
                                    "bootset":	false
                                }, {
                                    "name":	"ota_0",
                                    "size":	4259840,
                                    "version":	"",
                                    "ota":	true,
                                    "valid":	true,
                                    "running":	true,
                                    "bootset":	true
                                }, {
                                    "name":	"ota_1",
                                    "size":	4259840,
                                    "version":	"",
                                    "ota":	true,
                                    "valid":	true,
                                    "running":	false,
                                    "bootset":	false
                                }],
                            "data":	[{
                                    "name":	"nvs",
                                    "size":	16384,
                                    "format":	2
                                }, {
                                    "name":	"otadata",
                                    "size":	8192,
                                    "format":	0
                                }, {
                                    "name":	"phy_init",
                                    "size":	4096,
                                    "format":	1
                                }, {
                                    "name":	"internalfs",
                                    "size":	3932160,
                                    "format":	129
                                }]
                        }

/setboot:
    description: boot flag
    get:
        description: Set the boot flag.  example GET /flash/setboot?partition=ota_1
        queryParameters:
            partition:
                displayName: Partition
                type: string
                description: String name of partition (i.e. factory, ota_0, ota_1).  If not specified, just return the current setting.
                example: ota_0
                required: false
        responses:
            200:
                body:
                    application/json:
                      type: object
                      properties:
                        success: boolean
                        boot: string
                      example: |
                        {
                          "success": true
                          "boot": "ota_0"
                        }
                        
/reboot:
    description: Reboot the processor
    get:
        description: Reboot the processor.  example GET /flash/reboot
        responses:
            200:
                body:
                    application/json:
                      type: object
                      properties:
                        success: boolean
                        message: string
                      example: |
                        {
                          "success": true
                          "message": "Rebooting..."
                        }
                        

/upload:
    description: Upload APP firmware to flash memory
    post:
        description: Upload APP firmware to flash memory.
        queryParameters:
            partition:
                displayName: Partition
                type: string
                description: String name of partition (i.e. factory, ota_0, ota_1).  If not specified, automatically choose the next available OTA slot.
                example: ota_0
                required: false
        responses:
            200:
                body:
                    application/json:
                      type: object
                      properties:
                        success: boolean
                        message: string
                      example: |
                          {
                              "success": true
                              "message": "Flash Success."
                          }
```
