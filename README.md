Map-Generator
=============
Simple map/terrain generator that supports exporting to OTBM, LUA, JSON and PNG.
Work in progress!

### Available parameters
This application won't work without parameters, so here are they:
```
  --help, -H
            Displays available parameters
  --size, -S (REQUIRED)
            Arguments: size
            Sets generated map size
  --filename, -F (REQUIRED?)
            Name of file with the map, don't add extension!
            Required if there's no --prefix argument present
  --prefix, -P (REQUIRED?)
            Prefix for generated files, don't add extension!
            Required if there's no --filename argument present
  --count, -C
            Default value: 1
            Count of files to be generated
  --format
            Available formats: OTBM|PNG|JSON|LUA
            Default value: PNG
            Format of output file
            WARNING: Maximum size for OTBM maps is 250x250 SQM, but It'll be fixed in future.

            If OTBM format is chosen then map is saved in OTBMv2 version for client 8.60
            It can be then easily converted to other version in Remere's Map Editor
  --preset, -P
            Available presets: island
            Default value: island
            Preset for generated map;
```

### Map generation presets
At the moment there's only island preset, but more presets will be added soon!

**Island** preset examples:

![Island Preset Image](http://vestia.pl/images/uploader/13092014-8970894.png "Island Preset Image"),
![Island Preset Image](http://vestia.pl/images/uploader/13092014-7110481.png "Island Preset Image"),
![Island Preset Image](http://vestia.pl/images/uploader/13092014-6248562.png "Island Preset Image")

### How to use?
Here are some sample commands:
```
Generates 10 maps with 512x512 size and exports them to PNG files with map_ prefix.
./generator --size 512 --prefix map_ --count 10 --format PNG --preset island
```
```
Generates one 100x100 map and exports it to OTBM file with map.otbm file name
./generator --size 100 --filename map --format OTBM
```
