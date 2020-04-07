# KateBot-Remastered
It is an advanced and updated project of KateBot that everyone loves and uses for a long time.

## Features
* **Aimbot**
* **Triggerbot**
* **GlowESP**
* **Chams**
* **Radar**
* **Skin changer** - not stable
* **Bunnyhop**
* **Misc**
  * **FastReload**
  * **AspectRatio**
  * **GrenadePrediction**
  * **HitSound**
  * **NightMode**
  * **PostProcessing**
  * **RankReveal on ClientCMD**
  * **RecoilCrosshair**
  * **SkyBoxChanger**
  * **SniperCrosshair**
  * **ViewModel FOV Changer**
  
### Project Features
<details>

* **CVAR Manager**
* **BSPParser**
* **Input System**
* **PrimaryMonitorLock - Lock Mouse**

</details>
 

### Config.ini
<details>
 
```ini
;http://cherrytree.at/misc/vk.htm
[Keys]
;F5
Aimbot.Toggle = 116
;LMB
Aimbot.Hold = 1
;F7
GlowESP.Toggle = 118
;Left ALT
Triggerbot.Hold = 18
;Space
Bunnyhop.Hold = 32
;F8
Chams.Toggle = 119
;F6
Radar.Toggle = 117
;F4
NightMode.Toggle = 115
;INSERT
StreamMode.Toggle = 45

[Features]
Debug.Enable = false
StreamMode.Enable = true
Aimbot.Enable = true
GlowESP.Enable = false
Triggerbot.Enable = true
Bunnyhop.Enable = true
Skinchanger.Enable = true
Chams.Enable = true
Radar.Enable = false
NightMode.Enable = true
FastReload.Enable = false
AspectRatio.Enable = true
GrenadePrediction.Enable = false
RecoilCrosshair.Enable = true
SkyBoxChanger.Enable = true
ViewModelFOV.Enable = true
DisablePostProcessing.Enable = true
SniperCrosshair.Enable = true
HitSound.Enable = true
RevealRank.Enable = true

[Aimbot]
Spiral.Enable = true
Spiral.X = 5.2
Spiral.Y = 8.7
SaveTarget.Enable = false
SprayFOV.Enable = true
FaceitMode.Enable = true

AdaptiveSmooth.Rifles = true
AdaptiveSmooth.Pistol = true
AdaptiveSmooth.Sniper = false
AdaptiveSmooth.SMG = true
AdaptiveSmooth.Shotgun = true
AdaptiveSmooth.LMG = true

AdaptiveSmooth.Rifles.Multiplier = 36
AdaptiveSmooth.Pistol.Multiplier = 15
AdaptiveSmooth.Sniper.Multiplier = 10
AdaptiveSmooth.SMG.Multiplier = 36
AdaptiveSmooth.Shotgun.Multiplier = 60
AdaptiveSmooth.LMG.Multiplier = 60

[Triggerbot]
FovBased.Enable = true
Fov = 0.7
Delay = 1

[BSPParsing]
Enable = false

[AspectRatio]
Value = 17

[ViewModel]
Fov = 75

[Chams]
ModelAmbient.Enable = true
HealthBased.Enable = true
ViewModel.Enable = false
EnemiesOnly.Enable = true 

Brightness = 30

EnemyColor.Red = 255
EnemyColor.Green = 0
EnemyColor.Blue = 0
EnemyColor.Alpha = 255

AllyColor.Red = 127
AllyColor.Green = 255
AllyColor.Blue = 212
AllyColor.Alpha = 255

C4Bomb.Red = 255
C4Bomb.Green = 0
C4Bomb.Blue = 147
C4Bomb.Alpha = 255

C4Player.Red = 255
C4Player.Green = 0
C4Player.Blue = 147
C4Player.Alpha = 255

DefusePlayer.Red = 255
DefusePlayer.Green = 0
DefusePlayer.Blue = 147
DefusePlayer.Alpha = 255

[NightMode]
Amount = 0.1

[Skybox]
Name = sky_csgo_cloudy01

[SkinChanger]
Knife.Enable = true
AutoUpdate.Enable = true
Knife = KARAMBIT
Knife.SkinID = 569

[GlowESP]
NoFlicker.Enable = true
EnemiesOnly.Enable = true
OnlyVisible.Enable = false
HealthBased.Enable = false
Color.Red = 255
Color.Green = 0
Color.Blue = 0
Color.Alpha = 70

[Rifles]
ak47.aimbot.enable=true
ak47.aimbot.start=0
ak47.aimbot.end=30
ak47.aimbot.delay=0
ak47.aimbot.fov=2.5
ak47.aimbot.smooth=12
ak47.aimbot.bone=0
ak47.aimbot.rcsAmount=2.2
ak47.aimbot.killDelay=500
ak47.skin.id=707
ak47.skin.statTrack=1337
 
m4a4.aimbot.enable=true
m4a4.aimbot.start=0
m4a4.aimbot.end=30
m4a4.aimbot.delay=0
m4a4.aimbot.fov=2.5
m4a4.aimbot.smooth=12
m4a4.aimbot.bone=0
m4a4.aimbot.rcsAmount=2.2
m4a4.aimbot.killDelay=500
m4a4.skin.id=309
m4a4.skin.statTrack=1337
 
m4a1s.aimbot.enable=true
m4a1s.aimbot.start=0
m4a1s.aimbot.end=30
m4a1s.aimbot.delay=0
m4a1s.aimbot.fov=2.5
m4a1s.aimbot.smooth=12
m4a1s.aimbot.bone=0
m4a1s.aimbot.rcsAmount=2
m4a1s.aimbot.killDelay=500
m4a1s.skin.id=497
m4a1s.skin.statTrack=2532
 
aug.aimbot.enable=true
aug.aimbot.start=0
aug.aimbot.end=30
aug.aimbot.delay=0
aug.aimbot.fov=2.5
aug.aimbot.smooth=12
aug.aimbot.bone=0
aug.aimbot.rcsAmount=2
aug.aimbot.killDelay=500
aug.skin.id=455
aug.skin.statTrack=2532
 
ssg553.aimbot.enable=true
ssg553.aimbot.start=0
ssg553.aimbot.end=30
ssg553.aimbot.delay=0
ssg553.aimbot.fov=2.5
ssg553.aimbot.smooth=12
ssg553.aimbot.bone=0
ssg553.aimbot.rcsAmount=2
ssg553.aimbot.killDelay=500
ssg553.skin.id=487
ssg553.skin.statTrack=2532
 
famas.aimbot.enable=true
famas.aimbot.start=0
famas.aimbot.end=30
famas.aimbot.delay=0
famas.aimbot.fov=2.5
famas.aimbot.smooth=12
famas.aimbot.bone=0
famas.aimbot.rcsAmount=2
famas.aimbot.killDelay=500
famas.skin.id=529
famas.skin.statTrack=2532
 
galil.aimbot.enable=true
galil.aimbot.start=0
galil.aimbot.end=30
galil.aimbot.delay=0
galil.aimbot.fov=2.5
galil.aimbot.smooth=12
galil.aimbot.bone=0
galil.aimbot.rcsAmount=2
galil.aimbot.killDelay=500
galil.skin.id=398
galil.skin.statTrack=2532
 
 
[Pistols]
deagle.aimbot.enable=true
deagle.aimbot.start=0
deagle.aimbot.end=7
deagle.aimbot.delay=0
deagle.aimbot.fov=3.2
deagle.aimbot.smooth=32
deagle.aimbot.bone=0
deagle.aimbot.rcsAmount=0.1
deagle.aimbot.killDelay=400
deagle.skin.id=527
deagle.skin.statTrack=2532
 
glock.aimbot.enable=true
glock.aimbot.start=0
glock.aimbot.end=20
glock.aimbot.delay=0
glock.aimbot.fov=4
glock.aimbot.smooth=50
glock.aimbot.bone=8
glock.aimbot.rcsAmount=0
glock.aimbot.killDelay=200
glock.skin.id=381
glock.skin.statTrack=2532
 
p2000.aimbot.enable=true
p2000.aimbot.start=0
p2000.aimbot.end=12
p2000.aimbot.delay=0
p2000.aimbot.fov=3
p2000.aimbot.smooth=50
p2000.aimbot.bone=8
p2000.aimbot.rcsAmount=0
p2000.aimbot.killDelay=200
p2000.skin.id=485
p2000.skin.statTrack=2532
 
usp.aimbot.enable=true
usp.aimbot.start=0
usp.aimbot.end=12
usp.aimbot.delay=0
usp.aimbot.fov=4
usp.aimbot.smooth=50
usp.aimbot.bone=8
usp.aimbot.rcsAmount=0
usp.aimbot.killDelay=200
usp.skin.id=504
usp.skin.statTrack=2532
 
p250.aimbot.enable=true
p250.aimbot.start=0
p250.aimbot.end=13
p250.aimbot.delay=50
p250.aimbot.fov=4
p250.aimbot.smooth=50
p250.aimbot.bone=8
p250.aimbot.rcsAmount=0
p250.aimbot.killDelay=100
p250.skin.id=813
p250.skin.statTrack=2532
 
tec9.aimbot.enable=true
tec9.aimbot.start=0
tec9.aimbot.end=0
tec9.aimbot.delay=20
tec9.aimbot.fov=3
tec9.aimbot.smooth=50
tec9.aimbot.bone=8
tec9.aimbot.rcsAmount=0
tec9.aimbot.killDelay=100
tec9.skin.id=309
tec9.skin.statTrack=2532
 
five_seven.aimbot.enable=true
five_seven.aimbot.start=0
five_seven.aimbot.end=0
five_seven.aimbot.delay=20
five_seven.aimbot.fov=3
five_seven.aimbot.smooth=50
five_seven.aimbot.bone=8
five_seven.aimbot.rcsAmount=0
five_seven.aimbot.killDelay=100
five_seven.skin.id=12
five_seven.skin.statTrack=2532
 
dual_berettas.aimbot.enable=true
dual_berettas.aimbot.start=0
dual_berettas.aimbot.end=0
dual_berettas.aimbot.delay=20
dual_berettas.aimbot.fov=3
dual_berettas.aimbot.smooth=50
dual_berettas.aimbot.bone=0
dual_berettas.aimbot.rcsAmount=1.5
dual_berettas.aimbot.killDelay=100
dual_berettas.skin.id=396
dual_berettas.skin.statTrack=2532
 
cz75.aimbot.enable=true
cz75.aimbot.start=0
cz75.aimbot.end=30
cz75.aimbot.delay=35
cz75.aimbot.fov=3
cz75.aimbot.smooth=40
cz75.aimbot.bone=0
cz75.aimbot.rcsAmount=1
cz75.aimbot.killDelay=100
cz75.skin.id=270
cz75.skin.statTrack=2532
 
r8.aimbot.enable=true
r8.aimbot.start=0
r8.aimbot.end=30
r8.aimbot.delay=0
r8.aimbot.fov=2
r8.aimbot.smooth=270
r8.aimbot.bone=0
r8.aimbot.rcsAmount=2
r8.aimbot.killDelay=100
r8.skin.id=0
r8.skin.statTrack=2532
 
zeus.aimbot.enable=false
zeus.aimbot.start=0
zeus.aimbot.end=30
zeus.aimbot.delay=100
zeus.aimbot.fov=20
zeus.aimbot.smooth=20
zeus.aimbot.bone=0
zeus.aimbot.rcsAmount=0
zeus.aimbot.killDelay=1000
zeus.skin.id=0
zeus.skin.statTrack=2532
 
[Snipers]
awp.aimbot.enable=true
awp.aimbot.start=0
awp.aimbot.end=10
awp.aimbot.delay=0
awp.aimbot.fov=2.5
awp.aimbot.smooth=10
awp.aimbot.bone=0
awp.aimbot.rcsAmount=0
awp.aimbot.killDelay=800
awp.skin.id=344
awp.skin.statTrack=2532
 
scout.aimbot.enable=true
scout.aimbot.start=0
scout.aimbot.end=10
scout.aimbot.delay=0
scout.aimbot.fov=2.5
scout.aimbot.smooth=10
scout.aimbot.bone=0
scout.aimbot.rcsAmount=0
scout.aimbot.killDelay=500
scout.skin.id=384
scout.skin.statTrack=2532
 
g3sg1.aimbot.enable=true
g3sg1.aimbot.start=0
g3sg1.aimbot.end=30
g3sg1.aimbot.delay=35
g3sg1.aimbot.fov=3
g3sg1.aimbot.smooth=100
g3sg1.aimbot.bone=0
g3sg1.aimbot.rcsAmount=1.2
g3sg1.aimbot.killDelay=500
g3sg1.skin.id=438
g3sg1.skin.statTrack=2532
 
scar-20.aimbot.enable=true
scar-20.aimbot.start=0
scar-20.aimbot.end=30
scar-20.aimbot.delay=35
scar-20.aimbot.fov=3
scar-20.aimbot.smooth=100
scar-20.aimbot.bone=0
scar-20.aimbot.rcsAmount=1.2
scar-20.aimbot.killDelay=500
scar-20.skin.id=391
scar-20.skin.statTrack=2532
 
[SMGs]
mac10.aimbot.enable=true
mac10.aimbot.start=0
mac10.aimbot.end=30
mac10.aimbot.delay=0
mac10.aimbot.fov=2
mac10.aimbot.smooth=10
mac10.aimbot.bone=0
mac10.aimbot.rcsAmount=2
mac10.aimbot.killDelay=500
mac10.skin.id=433
mac10.skin.statTrack=2532
 
p90.aimbot.enable=true
p90.aimbot.start=0
p90.aimbot.end=30
p90.aimbot.delay=0
p90.aimbot.fov=2
p90.aimbot.smooth=10
p90.aimbot.bone=0
p90.aimbot.rcsAmount=2
p90.aimbot.killDelay=500
p90.skin.id=359
p90.skin.statTrack=2532

mp5-sd.aimbot.enable=true
mp5-sd.aimbot.start=0
mp5-sd.aimbot.end=30
mp5-sd.aimbot.delay=0
mp5-sd.aimbot.fov=2
mp5-sd.aimbot.smooth=10
mp5-sd.aimbot.bone=0
mp5-sd.aimbot.rcsAmount=2
mp5-sd.aimbot.killDelay=500
mp5-sd.skin.id=810
mp5-sd.skin.statTrack=2532
 
ump45.aimbot.enable=true
ump45.aimbot.start=0
ump45.aimbot.end=30
ump45.aimbot.delay=0
ump45.aimbot.fov=2
ump45.aimbot.smooth=10
ump45.aimbot.bone=0
ump45.aimbot.rcsAmount=2
ump45.aimbot.killDelay=500
ump45.skin.id=556
ump45.skin.statTrack=2532
 
bizon.aimbot.enable=true
bizon.aimbot.start=0
bizon.aimbot.end=30
bizon.aimbot.delay=0
bizon.aimbot.fov=2
bizon.aimbot.smooth=10
bizon.aimbot.bone=0
bizon.aimbot.rcsAmount=2
bizon.aimbot.killDelay=500
bizon.skin.id=13
bizon.skin.statTrack=2532
 
mp7.aimbot.enable=true
mp7.aimbot.start=0
mp7.aimbot.end=30
mp7.aimbot.delay=0
mp7.aimbot.fov=2
mp7.aimbot.smooth=10
mp7.aimbot.bone=0
mp7.aimbot.rcsAmount=2
mp7.aimbot.killDelay=500
mp7.skin.id=481
mp7.skin.statTrack=2532
 
mp9.aimbot.enable=true
mp9.aimbot.start=0
mp9.aimbot.end=30
mp9.aimbot.delay=0
mp9.aimbot.fov=2
mp9.aimbot.smooth=10
mp9.aimbot.bone=0
mp9.aimbot.rcsAmount=2
mp9.aimbot.killDelay=500
mp9.skin.id=39
mp9.skin.statTrack=2532
 
[Shotguns]
xm1014.aimbot.enable=true
xm1014.aimbot.start=0
xm1014.aimbot.end=0
xm1014.aimbot.delay=50
xm1014.aimbot.fov=5
xm1014.aimbot.smooth=20
xm1014.aimbot.bone=0
xm1014.aimbot.rcsAmount=0
xm1014.aimbot.killDelay=500
xm1014.skin.id=370
xm1014.skin.statTrack=2532
 
mag7.aimbot.enable=true
mag7.aimbot.start=0
mag7.aimbot.end=0
mag7.aimbot.delay=50
mag7.aimbot.fov=5
mag7.aimbot.smooth=20
mag7.aimbot.bone=0
mag7.aimbot.rcsAmount=0
mag7.aimbot.killDelay=500
mag7.skin.id=535
mag7.skin.statTrack=2532
 
sawed_off.aimbot.enable=true
sawed_off.aimbot.start=0
sawed_off.aimbot.end=0
sawed_off.aimbot.delay=50
sawed_off.aimbot.fov=5
sawed_off.aimbot.smooth=20
sawed_off.aimbot.bone=0
sawed_off.aimbot.rcsAmount=0
sawed_off.aimbot.killDelay=500
sawed_off.skin.id=256
sawed_off.skin.statTrack=2532
 
nova.aimbot.enable=true
nova.aimbot.start=0
nova.aimbot.end=0
nova.aimbot.delay=50
nova.aimbot.fov=5
nova.aimbot.smooth=20
nova.aimbot.bone=0
nova.aimbot.rcsAmount=0
nova.aimbot.killDelay=500
nova.skin.id=286
nova.skin.statTrack=2532
 
[LMG]
m249.aimbot.enable=true
m249.aimbot.start=0
m249.aimbot.end=30
m249.aimbot.delay=35
m249.aimbot.fov=3
m249.aimbot.smooth=50
m249.aimbot.bone=6
m249.aimbot.rcsAmount=2
m249.aimbot.killDelay=100
m249.skin.id=496
m249.skin.statTrack=2532
 
negev.aimbot.enable=true
negev.aimbot.start=0
negev.aimbot.end=30
negev.aimbot.delay=35
negev.aimbot.fov=3
negev.aimbot.smooth=50
negev.aimbot.bone=6
negev.aimbot.rcsAmount=2
negev.aimbot.killDelay=100
negev.skin.id=483
negev.skin.statTrack=2532
```

</details>

![ImageFromTrain](https://i.imgur.com/4O4BFzD.jpg)
