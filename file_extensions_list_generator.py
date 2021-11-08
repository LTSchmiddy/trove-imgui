raw = """
.ASX	Advanced Stream Redirector
.DTS	Digital Theater Systems Audio File
.GXF	General eXchange Format
.M2V	MPEG-2 Video
.M3U	MP3 Uniform Resource Locator
.M4V	MPEG-4 Video File
.MPEG1	MPEG-1 Video
.MPEG2	MPEG-2 Video
.MTS	AVCHD Video File
.MXF	Material eXchange Format
.OGM	Ogg Multimedia Container File
.PLS	Playlist
.BUP	DVD Information File
.A52	Dolby Digital AC-3 Compressed Audio File
.AAC	Advanced Audio Coding Compressed Audio File
.B4S	Winamp 3+ Playlist
.CUE	Cue Sheet
.DIVX	DivX Movie
.DV	Digital Video
.FLV	Flash Video
.M1V	MPEG-1 Video
.M2TS	MPEG-2 Transport Stream Videos
.MKV	Matroska Video Stream
.MOV	Apple QuickTime Movie
.MPEG4	MPEG-4 Video
.OMA	OpenMG Audio File
.SPX	Ogg Speex Audio File
.TS	DVD Video
.VLC	VLC Media Player Data
.VOB	DVD Video Object
.XSPF	XML Shareable Playlist Format
.DAT	VCD Video
.BIN	Binary DVD Video
.IFO	DVD Information File
.PART	Partially Downloaded File
.3G2	3G Mobile Phone Video
.AVI	Audio Video Interleave
.MPEG	MPEG Video
.MPG	MPEG Video
.FLAC	Free Lossless Audio Codec Compressed Audio FIle
.M4A	MPEG-4 Audio File
.MP1	MPEG-1 Audio Layer I
.OGG	Ogg Multimedia Container File
.WAV	Waveform Audio
.XM	Extended Module Audio File
.3GP	3G Mobile Phone Video
.SRT	DVD Subtitles File
.WMV	Windows Media Video
.AC3	Dolby Digital AC-3 Compressed Audio File
.ASF	Advanced Systems Format Video
.MOD	MOD Audio File
.MP2	MPEG-1 Audio Layer II
.MP3	MPEG-1 Audio Layer 3
.MP4	MPEG-4 Part 14 Multimedia Container
.WMA	Windows Media Audio File
.MKA	Matroska Audio Stream
.M4P	Protected AAC File
"""

retVal = {}

for i in raw.split("\n"):
    if i.strip() == "":
        continue
    
    print (f"{i=}")
    ext, desc = i.split("\t")
    
    retVal[ext] = desc
    
print (retVal)

import json
ext_file = open("vlc_known_extensions.json", "w")
json.dump(retVal, ext_file, indent=4, sort_keys=True)
ext_file.close()