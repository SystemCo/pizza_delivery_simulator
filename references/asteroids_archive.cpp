
class Game {
    public:
        Ship ship;
        Asteroid *ahead;
        Bullet *barr;
        int nasteroids;
        int nbullets;
        struct timespec bulletTimer;
        struct timespec mouseThrustTimer;
        bool mouseThrustOn;
    public:
        void Build_Asteroid()
        {

            Asteroid *a = new Asteroid;
            a->nverts = 8;
            a->radius = rnd()*80.0 + 40.0;
            Flt r2 = a->radius / 2.0;
            Flt angle = 0.0f;
            Flt inc = (PI * 2.0) / (Flt)a->nverts;
            for (int i=0; i<a->nverts; i++) {
                a->vert[i][0] = sin(angle) * (r2 + rnd() * a->radius);
                a->vert[i][1] = cos(angle) * (r2 + rnd() * a->radius);
                angle += inc;
            }
            a->pos[0] = (Flt)(rand() % gl.xres);
            a->pos[1] = (Flt)(rand() % gl.yres);
            a->pos[2] = 0.0f;
            a->angle = 0.0;
            a->rotate = rnd() * 4.0 - 2.0;
            a->color[0] = 0.8;
            a->color[1] = 0.8;
            a->color[2] = 0.7;
            a->vel[0] = (Flt)(rnd()*2.0-1.0);
            a->vel[1] = (Flt)(rnd()*2.0-1.0);
            //std::cout << "asteroid" << std::endl;
            //add to front of linked list
            a->next = ahead;
            if (ahead != NULL)
                ahead->prev = a;
            ahead = a;
            ++nasteroids;
        }
        Game() {
            ahead = NULL;
            barr = new Bullet[MAX_BULLETS];
            nasteroids = 0;
            nbullets = 0;
            mouseThrustOn = false;
            //build 10 asteroids...
            for (int j=0; j<10; j++) {
                Build_Asteroid();
            }
            clock_gettime(CLOCK_REALTIME, &bulletTimer);
        }
        ~Game() {
            delete [] barr;
        }
} g;


class Ship {
    public:
        Vec pos;
        Vec dir;
        Vec vel;
        Vec acc;
        float angle;
        float color[3];
    public:
        Ship() {
            pos[0] = (Flt)(gl.xres/2);
            pos[1] = (Flt)(gl.yres/2);
            pos[2] = 0.0f;
            VecZero(dir);
            VecZero(vel);
            VecZero(acc);
            angle = 0.0;
            color[0] = color[1] = color[2] = 1.0;
        }
};

class Bullet {
    public:
        Vec pos;
        Vec vel;
        float color[3];
        struct timespec time;
    public:
        Bullet() { }
};

class Asteroid {
    public:
        Vec pos;
        Vec vel;
        int nverts;
        Flt radius;
        Vec vert[8];
        float angle;
        float rotate;
        float color[3];
        struct Asteroid *prev;
        struct Asteroid *next;
    public:
        Asteroid() {
            prev = NULL;
            next = NULL;
        }
};


void deleteAsteroid(Game *g, Asteroid *node)
{
    //Remove a node from doubly-linked list
    //Must look at 4 special cases below.
    if (node->prev == NULL) {
        if (node->next == NULL) {
            //only 1 item in list.
            g->ahead = NULL;
        } else {
            //at beginning of list.
            node->next->prev = NULL;
            g->ahead = node->next;
        }
    } else {
        if (node->next == NULL) {
            //at end of list.
            node->prev->next = NULL;
        } else {
            //in middle of list.
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    }
    delete node;
    node = NULL;
}

void buildAsteroidFragment(Asteroid *ta, Asteroid *a)
{
    //build ta from a
    ta->nverts = 8;
    ta->radius = a->radius / 2.0;
    Flt r2 = ta->radius / 2.0;
    Flt angle = 0.0f;
    Flt inc = (PI * 2.0) / (Flt)ta->nverts;
    for (int i=0; i<ta->nverts; i++) {
        ta->vert[i][0] = sin(angle) * (r2 + rnd() * ta->radius);
        ta->vert[i][1] = cos(angle) * (r2 + rnd() * ta->radius);
        angle += inc;
    }
    ta->pos[0] = a->pos[0] + rnd()*10.0-5.0;
    ta->pos[1] = a->pos[1] + rnd()*10.0-5.0;
    ta->pos[2] = 0.0f;
    ta->angle = 0.0;
    ta->rotate = a->rotate + (rnd() * 4.0 - 2.0);
    ta->color[0] = 0.8;
    ta->color[1] = 0.8;
    ta->color[2] = 0.7;
    ta->vel[0] = a->vel[0] + (rnd()*2.0-1.0);
    ta->vel[1] = a->vel[1] + (rnd()*2.0-1.0);
    //std::cout << "frag" << std::endl;
}



void physics()
{
    Flt d0,d1,dist;
    //Update ship position
    g.ship.pos[0] += g.ship.vel[0];
    g.ship.pos[1] += g.ship.vel[1];
    //Check for collision with window edges
    if (g.ship.pos[0] < 0.0) {
        g.ship.pos[0] += (float)gl.xres;
    }
    else if (g.ship.pos[0] > (float)gl.xres) {
        g.ship.pos[0] -= (float)gl.xres;
    }
    else if (g.ship.pos[1] < 0.0) {
        g.ship.pos[1] += (float)gl.yres;
    }
    else if (g.ship.pos[1] > (float)gl.yres) {
        g.ship.pos[1] -= (float)gl.yres;
    }
    //
    //
    //Update bullet positions
    struct timespec bt;
    clock_gettime(CLOCK_REALTIME, &bt);
    int i = 0;
    while (i < g.nbullets) {
        Bullet *b = &g.barr[i];
        //How long has bullet been alive?
        double ts = timeDiff(&b->time, &bt);
        if (ts > 2.5) {
            //time to delete the bullet.
            memcpy(&g.barr[i], &g.barr[g.nbullets-1],
                    sizeof(Bullet));
            g.nbullets--;
            //do not increment i.
            continue;
        }
        //move the bullet
        b->pos[0] += b->vel[0];
        b->pos[1] += b->vel[1];
        //Check for collision with window edges
        if (b->pos[0] < 0.0) {
            b->pos[0] += (float)gl.xres;
        }
        else if (b->pos[0] > (float)gl.xres) {
            b->pos[0] -= (float)gl.xres;
        }
        else if (b->pos[1] < 0.0) {
            b->pos[1] += (float)gl.yres;
        }
        else if (b->pos[1] > (float)gl.yres) {
            b->pos[1] -= (float)gl.yres;
        }
        ++i;
    }
    //
    //Update asteroid positions
    Asteroid *a = g.ahead;
    while (a) {
        a->pos[0] += a->vel[0];
        a->pos[1] += a->vel[1];
        //Check for collision with window edges
        if (a->pos[0] < -100.0) {
            a->pos[0] += (float)gl.xres+200;
        }
        else if (a->pos[0] > (float)gl.xres+100) {
            a->pos[0] -= (float)gl.xres+200;
        }
        else if (a->pos[1] < -100.0) {
            a->pos[1] += (float)gl.yres+200;
        }
        else if (a->pos[1] > (float)gl.yres+100) {
            a->pos[1] -= (float)gl.yres+200;
        }
        a->angle += a->rotate;
        a = a->next;
    }
    //
    //Asteroid collision with bullets?
    //If collision detected:
    //     1. delete the bullet
    //     2. break the asteroid into pieces
    //        if asteroid small, delete it
    a = g.ahead;
    while (a) {
        //is there a bullet within its radius?
        int i=0;
        while (i < g.nbullets) {
            Bullet *b = &g.barr[i];
            d0 = b->pos[0] - a->pos[0];
            d1 = b->pos[1] - a->pos[1];
            dist = (d0*d0 + d1*d1);
            if (dist < (a->radius*a->radius)) {
                //std::cout << "asteroid hit." << std::endl;
                //this asteroid is hit.
                if (a->radius > MINIMUM_ASTEROID_SIZE) {
                    //break it into pieces.
                    Asteroid *ta = a;
                    buildAsteroidFragment(ta, a);
                    int r = rand()%10+5;
                    for (int k=0; k<r; k++) {
                        //get the next asteroid position in the array
                        Asteroid *ta = new Asteroid;
                        buildAsteroidFragment(ta, a);
                        //add to front of asteroid linked list
                        ta->next = g.ahead;
                        if (g.ahead != NULL)
                            g.ahead->prev = ta;
                        g.ahead = ta;
                        g.nasteroids++;
                    }
                } else {
                    a->color[0] = 1.0;
                    a->color[1] = 0.1;
                    a->color[2] = 0.1;
                    //asteroid is too small to break up
                    //delete the asteroid and bullet
                    Asteroid *savea = a->next;
                    deleteAsteroid(&g, a);
                    a = savea;
                    g.nasteroids--;
                }
                //delete the bullet...
                memcpy(&g.barr[i], &g.barr[g.nbullets-1], sizeof(Bullet));
                g.nbullets--;
                if (a == NULL)
                    break;
            }
            i++;
        }
        if (a == NULL)
            break;
        a = a->next;
    }
    //---------------------------------------------------
    //check keys pressed now
    if (gl.keys[XK_Left]) {
        g.ship.angle += 4.0;
        if (g.ship.angle >= 360.0f)
            g.ship.angle -= 360.0f;
    }
    if (gl.keys[XK_Right]) {
        g.ship.angle -= 4.0;
        if (g.ship.angle < 0.0f)
            g.ship.angle += 360.0f;
    }
    if (gl.keys[XK_Up]) {
        //apply thrust
        //convert ship angle to radians
        Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
        //convert angle to a vector
        Flt xdir = cos(rad);
        Flt ydir = sin(rad);
        g.ship.vel[0] += xdir*0.02f;
        g.ship.vel[1] += ydir*0.02f;
        Flt speed = sqrt(g.ship.vel[0]*g.ship.vel[0]+
                g.ship.vel[1]*g.ship.vel[1]);
        if (speed > 10.0f) {
            speed = 10.0f;
            normalize2d(g.ship.vel);
            g.ship.vel[0] *= speed;
            g.ship.vel[1] *= speed;
        }
    }

    if (gl.keys[XK_space]) {
        //a little time between each bullet
        struct timespec bt;
        clock_gettime(CLOCK_REALTIME, &bt);
        double ts = timeDiff(&g.bulletTimer, &bt);
        if (ts > 0.1) {
            timeCopy(&g.bulletTimer, &bt);
            if (g.nbullets < MAX_BULLETS) {
                //shoot a bullet...
                //Bullet *b = new Bullet;
                Bullet *b = &g.barr[g.nbullets];
                timeCopy(&b->time, &bt);
                b->pos[0] = g.ship.pos[0];
                b->pos[1] = g.ship.pos[1];
                b->vel[0] = g.ship.vel[0];
                b->vel[1] = g.ship.vel[1];
                //convert ship angle to radians
                Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
                //convert angle to a vector
                Flt xdir = cos(rad);
                Flt ydir = sin(rad);
                b->pos[0] += xdir*20.0f;
                b->pos[1] += ydir*20.0f;
                b->vel[0] += xdir*6.0f + rnd()*0.1;
                b->vel[1] += ydir*6.0f + rnd()*0.1;
                b->color[0] = 1.0f;
                b->color[1] = 1.0f;
                b->color[2] = 1.0f;
                g.nbullets++;
            }
        }
    }
    if (g.mouseThrustOn) {
        //should thrust be turned off
        struct timespec mtt;
        clock_gettime(CLOCK_REALTIME, &mtt);
        double tdif = timeDiff(&mtt, &g.mouseThrustTimer);
        //std::cout << "tdif: " << tdif << std::endl;
        if (tdif < -0.3)
            g.mouseThrustOn = false;
    }
}

void render()
{
    //-------------------------------------------------------------------------
    //Draw the ship
    glColor3fv(g.ship.color);
    glPushMatrix();
    glTranslatef(g.ship.pos[0], g.ship.pos[1], g.ship.pos[2]);
    //float angle = atan2(ship.dir[1], ship.dir[0]);
    glRotatef(g.ship.angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    //glVertex2f(-10.0f, -10.0f);
    //glVertex2f(  0.0f, 20.0f);
    //glVertex2f( 10.0f, -10.0f);
    glVertex2f(-12.0f, -10.0f);
    glVertex2f(  0.0f,  20.0f);
    glVertex2f(  0.0f,  -6.0f);
    glVertex2f(  0.0f,  -6.0f);
    glVertex2f(  0.0f,  20.0f);
    glVertex2f( 12.0f, -10.0f);
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f);
    glEnd();
    glPopMatrix();
    if (gl.keys[XK_Up] || g.mouseThrustOn) {
        int i;
        //draw thrust
        Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
        //convert angle to a vector
        Flt xdir = cos(rad);
        Flt ydir = sin(rad);
        Flt xs,ys,xe,ye,r;
        glBegin(GL_LINES);
        for (i=0; i<16; i++) {
            xs = -xdir * 11.0f + rnd() * 4.0 - 2.0;
            ys = -ydir * 11.0f + rnd() * 4.0 - 2.0;
            r = rnd()*40.0+40.0;
            xe = -xdir * r + rnd() * 18.0 - 9.0;
            ye = -ydir * r + rnd() * 18.0 - 9.0;
            glColor3f(rnd()*.3+.7, rnd()*.3+.7, 0);
            glVertex2f(g.ship.pos[0]+xs,g.ship.pos[1]+ys);
            glVertex2f(g.ship.pos[0]+xe,g.ship.pos[1]+ye);
        }
        glEnd();
    }
    //-------------------------------------------------------------------------
    //Draw the asteroids
    {
        Asteroid *a = g.ahead;
        while (a) { // a is null when it reaches the end of the linked list.
            //Log("draw asteroid...\n");
            glColor3fv(a->color);
            glPushMatrix();
            glTranslatef(a->pos[0], a->pos[1], a->pos[2]);
            glRotatef(a->angle, 0.0f, 0.0f, 1.0f);
            glBegin(GL_LINE_LOOP);
            //Log("%i verts\n",a->nverts);
                for (int j=0; j<a->nverts; j++) {
                    glVertex2f(a->vert[j][0], a->vert[j][1]);
                }
            glEnd();
            //glBegin(GL_LINES);
            //  glVertex2f(0,   0);
            //  glVertex2f(a->radius, 0);
            //glEnd();
            glPopMatrix();
            glColor3f(1.0f, 0.0f, 0.0f);
            glBegin(GL_POINTS);
            glVertex2f(a->pos[0], a->pos[1]);
            glEnd();
            a = a->next;
        }
    }
    //-------------------------------------------------------------------------
    //Draw the bullets
    for (int i=0; i<g.nbullets; i++) {
        Bullet *b = &g.barr[i];
        //Log("draw bullet...\n");
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2f(b->pos[0],      b->pos[1]);
        glVertex2f(b->pos[0]-1.0f, b->pos[1]);
        glVertex2f(b->pos[0]+1.0f, b->pos[1]);
        glVertex2f(b->pos[0],      b->pos[1]-1.0f);
        glVertex2f(b->pos[0],      b->pos[1]+1.0f);
        glColor3f(0.8, 0.8, 0.8);
        glVertex2f(b->pos[0]-1.0f, b->pos[1]-1.0f);
        glVertex2f(b->pos[0]-1.0f, b->pos[1]+1.0f);
        glVertex2f(b->pos[0]+1.0f, b->pos[1]-1.0f);
        glVertex2f(b->pos[0]+1.0f, b->pos[1]+1.0f);
        glEnd();
    }
}
