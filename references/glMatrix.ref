// From:
// https://stackoverflow.com/questions/23971752/understanding-glpushmatrix-and-glpopmatrix

glPushMatrix();          // Creates matrix 1 on the top
glTranslated(100, 0, 0); // Applies translation to matrix 1

drawSphere();            // Draws a sphere with translation <100, 0, 0>

glPushMatrix();          // Clones matrix 1 to create matrix 2 and pushes it on the top.
glScaled(2,2,2);         // Scales matrix 2; doesn't touch matrix 1

drawSphere();            // Draws a sphere with both translation <100, 0, 0> and scale <2,2,2>

glPopMatrix();           // Deletes matrix 2; matrix 1 becomes the top.

drawSphere();            // Same as the first sphere.

glPopMarix();            // Deletes matrix 1
