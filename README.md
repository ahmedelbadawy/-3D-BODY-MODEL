#  3D ROBOTIC BODY MODEL
## 1st Robotic Body and joints movements:

### Body & Head Part

-  First we draw the body cube and then we draw one side arm and leg ,translated them relative to the body cube .
The other arm and leg are translated with the same coordinates but with -ve x translations.
Each related body part was created in a separate push/pop matrix.





## 2nd Robotic Body parts Rotations


- s&S:For two shoulders (Up & Down)

- d&D: For two shoulders (Rotation around themselves)

- h&H: For two elbows

- e&E: For left femur (Right & Left)

- t&T: For right femur (Right & Left)
- q&Q: For left femur (Front & Back)
- w&W: For right femur (Front & Back)

- y&Y: For right tibia 
- u&U: For right tibia







## 3rd Camera Movement Part 
- We identify the projection plan using (glFrustum) then We create and locate camera using function (gluLookAt). We use function rotatePoint to rotate around up or horizontal axis and use functions moveBackword and moveForword to zoom in/out.


## results 
<img src = "https://i.ibb.co/1Q2fGMn/Whats-App-Image-2021-05-08-at-22-21-06-1.jpg">
<img src ="https://i.ibb.co/Y3pykRp/Whats-App-Image-2021-05-08-at-22-21-06.jpg">
<img src = "https://i.ibb.co/bXn0GNY/Whats-App-Image-2021-05-08-at-22-21-07.jpg">
<img src = "https://i.ibb.co/31Sym7L/Whats-App-Image-2021-05-08-at-22-21-07-1.jpg">

    





