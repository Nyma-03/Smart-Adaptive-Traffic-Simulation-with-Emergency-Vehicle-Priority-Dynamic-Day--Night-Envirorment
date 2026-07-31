#include <windows.h>  
#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

#define PI 3.14159265358979323846

GLfloat x, y, radius, twicePi;
int triangleAmount;

int frameNumber = 1;

// Boat positions
GLfloat position_b1 = -0.5f;
GLfloat speed_b1 = 0.002f;

GLfloat position_b2 = -1.5f;
GLfloat speed_b2 = 0.002f;

GLfloat position_r = -0.1f;
GLfloat speed_r = 0.01f;

GLfloat position_s = 1.6f;
GLfloat speed_s = 0.01f;

// Car positions - Horizontal Road (Road 1)
GLfloat position_c1 = 1.6f;
GLfloat speed_c1 = 0.01f;

GLfloat position_c2 = 2.4f;
GLfloat speed_c2 = 0.01f;

// Car positions - Vertical Road (Road 2)
GLfloat position_c3 = -0.9f;
GLfloat speed_c3 = 0.01f;

GLfloat position_c4 = 0.9f;
GLfloat speed_c4 = 0.01f;

// Extra cars for congestion
GLfloat position_c1_extra = 0.2f;
GLfloat speed_c1_extra = 0.01f;

GLfloat position_c2_extra = 1.8f;
GLfloat speed_c2_extra = 0.01f;

GLfloat position_c3_extra = -1.7f;
GLfloat speed_c3_extra = 0.01f;

GLfloat position_c4_extra = 0.1f;
GLfloat speed_c4_extra = 0.01f;

// Rain
GLfloat position_rain = 0.0f;
GLfloat speed_rain = 0.05f;
GLfloat position_rain2 = 2.0f;
GLfloat speed_rain2 = 0.05f;

// Emergency vehicles
int ambulanceOn = 0;
int firetruckOn = 0;

GLfloat position_amb = -2.3f;
GLfloat speed_amb = 0.025f;

GLfloat position_fire = -1.3f;
GLfloat speed_fire = 0.025f;

GLfloat car1_shift = 0.0f;
GLfloat car3_shift = 0.0f;
GLfloat car4_shift = 0.0f;

// Congestion Control
int extraCarsOnRoad1 = 0;
int extraCarsOnRoad2 = 0;

// Emergency tracking
int ambulancePassed = 0;
int emergencyActive = 0;

// NEW: Alternating mode
int alternatingMode = 0;
int currentVehicle = 0;   // 0 = ambulance, 1 = firetruck

int cnt = 0, flag = 0, r = 0;
const char* c;

// ==================== DRAWING FUNCTIONS ====================
// (All drawing functions: windmill, tree, shop, house, factory, fence,
// road_footpath, traffic_light1, traffic_light2, road_light, boat1, boat2,
// boat1_shore, boat2_shore, car1_extra, car2_extra, car3_extra, car4_extra,
// car1, car2, car3, car4, river, redgreen1, redgreen2, redgreen_emergency,
// ambulance, firetruck, rain, start, day, night)
// These are EXACTLY as in your original code, except that day() and night()
// have been modified to show only the active vehicle when alternatingMode is on.
// They are included in full below.

// -------- Drawing functions (unchanged from your original) --------
// void windmill() { /* ... unchanged ... */ }
// void tree() { /* ... unchanged ... */ }
// void shop() { /* ... unchanged ... */ }
// void house() { /* ... unchanged ... */ }
// void factory() { /* ... unchanged ... */ }
// void fence() { /* ... unchanged ... */ }
// void road_footpath() { /* ... unchanged ... */ }
// void traffic_light1() { /* ... unchanged ... */ }
// void traffic_light2() { /* ... unchanged ... */ }
// void road_light() { /* ... unchanged ... */ }
// void boat1() { /* ... unchanged ... */ }
// void boat2() { /* ... unchanged ... */ }
// void boat1_shore() { /* ... unchanged ... */ }
// void boat2_shore() { /* ... unchanged ... */ }
// void car1_extra() { /* ... unchanged ... */ }
// void car2_extra() { /* ... unchanged ... */ }
// void car3_extra() { /* ... unchanged ... */ }
// void car4_extra() { /* ... unchanged ... */ }
// void car1() { /* ... unchanged ... */ }
// void car2() { /* ... unchanged ... */ }
// void car3() { /* ... unchanged ... */ }
// void car4() { /* ... unchanged ... */ }
// void river() { /* ... unchanged ... */ }
// void redgreen1() { /* ... unchanged ... */ }
// void redgreen2() { /* ... unchanged ... */ }
// void redgreen_emergency() { /* ... unchanged ... */ }
// void ambulance() { /* ... unchanged ... */ }
// void firetruck() { /* ... unchanged ... */ }
// void rain() { /* ... unchanged ... */ }
// void start() { /* ... unchanged ... */ }


void windmill() {
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    glTranslatef(1.6, 0.3, 0.0);
    glColor3ub(255, 102, 102);
    glBegin(GL_POLYGON);
    glVertex2f(-0.80f, 0.275f);
    glVertex2f(-0.80f, 0.25f);
    glVertex2f(-0.65f, 0.25f);
    glVertex2f(-0.65f, 0.275f);
    glEnd();

    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2f(-0.775f, 0.5f);
    glVertex2f(-0.79f, 0.275f);
    glVertex2f(-0.66f, 0.275f);
    glVertex2f(-0.675f, 0.5f);
    glEnd();

    glColor3ub(51, 153, 255);
    glBegin(GL_POLYGON);
    glVertex2f(-0.71f, 0.35f);
    glVertex2f(-0.71f, 0.275f);
    glVertex2f(-0.74f, 0.275f);
    glVertex2f(-0.74f, 0.35f);
    glEnd();

    glColor3ub(51, 153, 255);
    glBegin(GL_POLYGON);
    glVertex2f(-0.71f, 0.45f);
    glVertex2f(-0.71f, 0.4f);
    glVertex2f(-0.74f, 0.4f);
    glVertex2f(-0.74f, 0.45f);
    glEnd();

    glColor3ub(00, 102, 204);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.79f, 0.5f);
    glVertex2f(-0.725f, 0.63f);
    glVertex2f(-0.66f, 0.5f);
    glEnd();

    glTranslatef(-0.725f, 0.55f, 0.0f);
    glRotated(frameNumber * (-180.0 / 500), 0, 0, 1);

    glColor3ub(204, 229, 255);
    glBegin(GL_POLYGON);
    glVertex2f(0.00f, 0.01f);
    glVertex2f(0.00f, 0.00f);
    glVertex2f(0.20f, 0.00f);
    glVertex2f(0.20f, 0.01f);
    glEnd();

    glColor3ub(255, 51, 51);
    glBegin(GL_POLYGON);
    glVertex2f(0.03f, 0.05f);
    glVertex2f(0.03f, 0.01f);
    glVertex2f(0.20f, 0.01f);
    glVertex2f(0.20f, 0.05f);
    glEnd();

    glColor3ub(204, 229, 255);
    glBegin(GL_POLYGON);
    glVertex2f(0.00f, 0.01f);
    glVertex2f(0.00f, 0.00f);
    glVertex2f(-0.20f, 0.00f);
    glVertex2f(-0.20f, 0.01f);
    glEnd();

    glColor3ub(255, 51, 51);
    glBegin(GL_POLYGON);
    glVertex2f(-0.03f, -0.04f);
    glVertex2f(-0.03f, -0.00f);
    glVertex2f(-0.20f, -0.00f);
    glVertex2f(-0.20f, -0.04f);
    glEnd();

    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glColor3ub(204, 229, 255);
    glBegin(GL_POLYGON);
    glVertex2f(0.00f, 0.01f);
    glVertex2f(0.00f, 0.00f);
    glVertex2f(0.20f, 0.00f);
    glVertex2f(0.20f, 0.01f);
    glEnd();

    glColor3ub(255, 51, 51);
    glBegin(GL_POLYGON);
    glVertex2f(0.03f, 0.05f);
    glVertex2f(0.03f, 0.01f);
    glVertex2f(0.20f, 0.01f);
    glVertex2f(0.20f, 0.05f);
    glEnd();

    glColor3ub(204, 229, 255);
    glBegin(GL_POLYGON);
    glVertex2f(0.00f, 0.01f);
    glVertex2f(0.00f, 0.00f);
    glVertex2f(-0.20f, 0.00f);
    glVertex2f(-0.20f, 0.01f);
    glEnd();

    glColor3ub(255, 51, 51);
    glBegin(GL_POLYGON);
    glVertex2f(-0.03f, -0.04f);
    glVertex2f(-0.03f, -0.00f);
    glVertex2f(-0.20f, -0.00f);
    glVertex2f(-0.20f, -0.04f);
    glEnd();

    x = -0.0f; y = 0.0f; radius = .02f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(255, 51, 51);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    glLoadIdentity();
}

void tree() {
    glLineWidth(10.0f);
    glBegin(GL_LINES);
    glColor3ub(153, 51, 51);
    glVertex2f(-1.5f, 0.8f);
    glVertex2f(-1.5f, 0.55f);
    glEnd();
    x = -1.45f; y = 0.82f; radius = 0.08f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(0, 153, 51);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = -1.5f; y = 0.85f; radius = 0.08f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(0, 153, 51);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = -1.55f; y = 0.82f; radius = 0.08f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(0, 153, 51);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-1.53f, 0.85f);
    glVertex2f(-1.47f, 0.8f);
    glEnd();

    glLineWidth(10.0f);
    glBegin(GL_LINES);
    glColor3ub(153, 51, 51);
    glVertex2f(-0.8f, 0.8f);
    glVertex2f(-0.8f, 0.57f);
    glEnd();
    x = -0.85f; y = 0.82f; radius = 0.08f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(0, 153, 51);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = -0.8f; y = 0.85f; radius = 0.08f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(0, 153, 51);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = -0.75f; y = 0.82f; radius = 0.08f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(0, 153, 51);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(153, 51, 51);
    glVertex2f(1.55f, 0.65f);
    glVertex2f(1.55f, 0.8f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 153, 51);
    glVertex2f(1.45f, 0.7f);
    glVertex2f(1.55f, 0.95f);
    glVertex2f(1.65f, 0.7f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(153, 51, 51);
    glVertex2f(-0.2f, 0.65f);
    glVertex2f(-0.2f, 0.8f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 153, 51);
    glVertex2f(-0.3f, 0.7f);
    glVertex2f(-0.2f, 0.95f);
    glVertex2f(-0.1f, 0.7f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(153, 51, 51);
    glVertex2f(1.9f, 0.7f);
    glVertex2f(1.9f, 0.85f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 153, 51);
    glVertex2f(1.8f, 0.75f);
    glVertex2f(1.9f, 1.0f);
    glVertex2f(2.0f, 0.75f);
    glEnd();
}

void shop() {
    // Left shop
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-1.95f, 0.5f);
    glVertex2f(-1.95f, 0.75f);
    glVertex2f(-1.55f, 0.75f);
    glVertex2f(-1.55f, 0.5f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(128, 0, 0);
    glVertex2f(-1.95f, 0.75f);
    glVertex2f(-1.95f, 0.85f);
    glVertex2f(-1.55f, 0.85f);
    glVertex2f(-1.55f, 0.75f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex2f(-2.0f, 0.65f);
    glVertex2f(-1.5f, 0.65f);
    glVertex2f(-1.5f, 0.7f);
    glVertex2f(-1.55f, 0.75f);
    glVertex2f(-1.95f, 0.75f);
    glVertex2f(-2.0f, 0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 230, 230);
    glVertex2f(-1.9f, 0.5f);
    glVertex2f(-1.9f, 0.62f);
    glColor3ub(0, 153, 153);
    glVertex2f(-1.82f, 0.62f);
    glVertex2f(-1.82f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 230, 230);
    glVertex2f(-1.77f, 0.55f);
    glVertex2f(-1.77f, 0.62f);
    glColor3ub(0, 153, 153);
    glVertex2f(-1.6f, 0.62f);
    glVertex2f(-1.6f, 0.55f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 0, 0);
    glVertex2f(-1.52f, 0.5f);
    glVertex2f(-1.98f, 0.5f);
    glVertex2f(-1.524f, 0.504f);
    glVertex2f(-1.98f, 0.504f);
    glVertex2f(-1.9f, 0.5f);
    glVertex2f(-1.9f, 0.62f);
    glVertex2f(-1.9f, 0.62f);
    glVertex2f(-1.82f, 0.62f);
    glVertex2f(-1.82f, 0.62f);
    glVertex2f(-1.82f, 0.5f);
    glVertex2f(-1.82f, 0.5f);
    glVertex2f(-1.9f, 0.5f);
    glVertex2f(-1.82f, 0.55f);
    glVertex2f(-1.9f, 0.55f);
    glVertex2f(-1.77f, 0.55f);
    glVertex2f(-1.77f, 0.62f);
    glVertex2f(-1.77f, 0.62f);
    glVertex2f(-1.6f, 0.62f);
    glVertex2f(-1.6f, 0.62f);
    glVertex2f(-1.6f, 0.55f);
    glVertex2f(-1.6f, 0.55f);
    glVertex2f(-1.77f, 0.55f);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    c = "BFC";
    glRasterPos2f(-1.8, 0.78);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);

    // Right shop
    glBegin(GL_POLYGON);
    glColor3ub(255, 204, 102);
    glVertex2f(-0.75f, 0.5f);
    glVertex2f(-0.75f, 0.8f);
    glVertex2f(-0.2f, 0.8f);
    glVertex2f(-0.2f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(179, 89, 0);
    glVertex2f(-0.75f, 0.85f);
    glVertex2f(-0.75f, 0.8f);
    glVertex2f(-0.2f, 0.8f);
    glVertex2f(-0.2f, 0.85f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(179, 89, 0);
    glVertex2f(-0.3f, 0.85f);
    glVertex2f(-0.35f, 0.9f);
    glVertex2f(-0.6f, 0.9f);
    glVertex2f(-0.66f, 0.85f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(77, 38, 0);
    glVertex2f(-0.73f, 0.6f);
    glVertex2f(-0.73f, 0.75f);
    glVertex2f(-0.22f, 0.75f);
    glVertex2f(-0.22f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex2f(-0.7f, 0.6f);
    glVertex2f(-0.7f, 0.65f);
    glVertex2f(-0.6f, 0.65f);
    glVertex2f(-0.6f, 0.6f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 204, 102);
    glVertex2f(-0.65f, 0.65f);
    glVertex2f(-0.65f, 0.68f);
    glVertex2f(-0.6f, 0.68f);
    glVertex2f(-0.6f, 0.65f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 204, 102);
    glVertex2f(-0.55f, 0.6f);
    glVertex2f(-0.55f, 0.65f);
    glVertex2f(-0.45f, 0.65f);
    glVertex2f(-0.45f, 0.6f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(204, 0, 102);
    glVertex2f(-0.4f, 0.6f);
    glVertex2f(-0.4f, 0.65f);
    glVertex2f(-0.35f, 0.6f);
    glVertex2f(-0.35f, 0.65f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 204, 102);
    glVertex2f(-0.34f, 0.6f);
    glVertex2f(-0.34f, 0.66f);
    glVertex2f(-0.3f, 0.6f);
    glVertex2f(-0.3f, 0.66f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(128, 64, 0);
    glVertex2f(-0.73f, 0.5f);
    glVertex2f(-0.73f, 0.6f);
    glVertex2f(-0.22f, 0.6f);
    glVertex2f(-0.22f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(230, 115, 0);
    glVertex2f(-0.8f, 0.7f);
    glVertex2f(-0.15f, 0.7f);
    glVertex2f(-0.15f, 0.75f);
    glVertex2f(-0.2f, 0.8f);
    glVertex2f(-0.75f, 0.8f);
    glVertex2f(-0.8f, 0.75f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 0, 0);
    glVertex2f(-0.17f, 0.5f);
    glVertex2f(-0.77f, 0.5f);
    glVertex2f(-0.17f, 0.504f);
    glVertex2f(-0.77f, 0.504f);
    glColor3ub(255, 153, 51);
    glVertex2f(-0.73f, 0.6f);
    glVertex2f(-0.22f, 0.6f);
    glEnd();

    glColor3ub(255, 255, 0);
    c = "Candy Shop";
    glRasterPos2f(-0.6, 0.84);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[i]);
}

void house() {
    // Left house
    glBegin(GL_POLYGON);
    glColor3ub(224, 228, 231);
    glVertex2f(-1.4f, 0.5f);
    glVertex2f(-1.4f, 1.0f);
    glVertex2f(-0.9f, 1.0f);
    glVertex2f(-0.9f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(179, 230, 255);
    glVertex2f(-1.35f, 0.55f);
    glVertex2f(-1.35f, 0.65f);
    glColor3ub(0, 230, 230);
    glVertex2f(-1.25f, 0.65f);
    glVertex2f(-1.25f, 0.55f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(179, 230, 255);
    glVertex2f(-1.05f, 0.55f);
    glVertex2f(-1.05f, 0.65f);
    glColor3ub(0, 230, 230);
    glVertex2f(-0.95f, 0.65f);
    glVertex2f(-0.95f, 0.55f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(179, 230, 255);
    glVertex2f(-1.35f, 0.85f);
    glVertex2f(-1.35f, 0.95f);
    glColor3ub(0, 230, 230);
    glVertex2f(-1.25f, 0.95f);
    glVertex2f(-1.25f, 0.85f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(179, 230, 255);
    glVertex2f(-1.2f, 0.85f);
    glVertex2f(-1.2f, 0.95f);
    glColor3ub(0, 230, 230);
    glVertex2f(-1.1f, 0.95f);
    glVertex2f(-1.1f, 0.85f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(179, 230, 255);
    glVertex2f(-1.05f, 0.85f);
    glVertex2f(-1.05f, 0.95f);
    glColor3ub(0, 230, 230);
    glVertex2f(-0.95f, 0.95f);
    glVertex2f(-0.95f, 0.85f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(153, 153, 153);
    glVertex2f(-1.2f, 0.5f);
    glVertex2f(-1.2f, 0.65f);
    glVertex2f(-1.1f, 0.65f);
    glVertex2f(-1.1f, 0.5f);
    glEnd();

    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-1.17f, 0.58f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(77, 195, 255);
    glVertex2f(-1.35f, 0.55f);
    glVertex2f(-1.35f, 0.65f);
    glVertex2f(-1.35f, 0.65f);
    glVertex2f(-1.25f, 0.65f);
    glVertex2f(-1.25f, 0.65f);
    glVertex2f(-1.25f, 0.55f);
    glVertex2f(-1.25f, 0.55f);
    glVertex2f(-1.35f, 0.55f);
    glVertex2f(-1.25f, 0.6f);
    glVertex2f(-1.35f, 0.6f);
    glVertex2f(-1.05f, 0.55f);
    glVertex2f(-1.05f, 0.65f);
    glVertex2f(-1.05f, 0.65f);
    glVertex2f(-0.95f, 0.65f);
    glVertex2f(-0.95f, 0.65f);
    glVertex2f(-0.95f, 0.55f);
    glVertex2f(-0.95f, 0.55f);
    glVertex2f(-1.05f, 0.55f);
    glVertex2f(-0.95f, 0.6f);
    glVertex2f(-1.05f, 0.6f);
    glVertex2f(-1.35f, 0.85f);
    glVertex2f(-1.35f, 0.95f);
    glVertex2f(-1.35f, 0.95f);
    glVertex2f(-1.25f, 0.95f);
    glVertex2f(-1.25f, 0.95f);
    glVertex2f(-1.25f, 0.85f);
    glVertex2f(-1.25f, 0.85f);
    glVertex2f(-1.35f, 0.85f);
    glVertex2f(-1.25f, 0.9f);
    glVertex2f(-1.35f, 0.9f);
    glVertex2f(-1.2f, 0.85f);
    glVertex2f(-1.2f, 0.95f);
    glVertex2f(-1.2f, 0.95f);
    glVertex2f(-1.1f, 0.95f);
    glVertex2f(-1.1f, 0.95f);
    glVertex2f(-1.1f, 0.85f);
    glVertex2f(-1.1f, 0.85f);
    glVertex2f(-1.2f, 0.85f);
    glVertex2f(-1.1f, 0.9f);
    glVertex2f(-1.2f, 0.9f);
    glVertex2f(-1.05f, 0.85f);
    glVertex2f(-1.05f, 0.95f);
    glVertex2f(-1.05f, 0.95f);
    glVertex2f(-0.95f, 0.95f);
    glVertex2f(-0.95f, 0.95f);
    glVertex2f(-0.95f, 0.85f);
    glVertex2f(-0.95f, 0.85f);
    glVertex2f(-1.05f, 0.85f);
    glVertex2f(-0.95f, 0.9f);
    glVertex2f(-1.05f, 0.9f);
    glVertex2f(-1.2f, 0.5f);
    glVertex2f(-1.2f, 0.65f);
    glVertex2f(-1.2f, 0.65f);
    glVertex2f(-1.1f, 0.65f);
    glVertex2f(-1.1f, 0.65f);
    glVertex2f(-1.1f, 0.5f);
    glVertex2f(-1.1f, 0.5f);
    glVertex2f(-1.2f, 0.5f);
    glColor3ub(128, 128, 128);
    glVertex2f(-1.4f, 0.5f);
    glVertex2f(-1.4f, 1.0f);
    glVertex2f(-1.4f, 1.0f);
    glVertex2f(-0.9f, 1.0f);
    glVertex2f(-0.9f, 1.0f);
    glVertex2f(-0.9f, 0.5f);
    glColor3ub(128, 0, 0);
    glVertex2f(-0.87f, 0.5f);
    glVertex2f(-1.43f, 0.5f);
    glVertex2f(-0.87f, 0.504f);
    glVertex2f(-1.43f, 0.504f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(76, 174, 218);
    glVertex2f(-1.4f, 0.8f);
    glVertex2f(-1.45f, 0.75f);
    glVertex2f(-1.45f, 0.7f);
    glVertex2f(-0.85f, 0.7f);
    glVertex2f(-0.85f, 0.75f);
    glVertex2f(-0.9f, 0.8f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(-1.4f, 0.8f);
    glVertex2f(-1.45f, 0.75f);
    glVertex2f(-1.45f, 0.75f);
    glVertex2f(-1.45f, 0.7f);
    glVertex2f(-1.45f, 0.7f);
    glVertex2f(-0.85f, 0.7f);
    glVertex2f(-0.85f, 0.7f);
    glVertex2f(-0.85f, 0.75f);
    glVertex2f(-0.85f, 0.75f);
    glVertex2f(-0.9f, 0.8f);
    glVertex2f(-0.9f, 0.8f);
    glVertex2f(-1.4f, 0.8f);
    glEnd();

    // Right house
    glBegin(GL_POLYGON);
    glColor3ub(153, 51, 0);
    glVertex2f(-0.15f, 0.5f);
    glVertex2f(-0.15f, 0.8f);
    glVertex2f(0.35f, 0.8f);
    glVertex2f(0.35f, 0.5f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(153, 51, 0);
    glVertex2f(0.05f, 0.8f);
    glVertex2f(0.05f, 0.99f);
    glVertex2f(0.35f, 0.99f);
    glVertex2f(0.35f, 0.8f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(77, 184, 255);
    glVertex2f(0.05f, 0.6f);
    glVertex2f(0.05f, 0.7f);
    glColor3ub(26, 140, 255);
    glVertex2f(0.15f, 0.7f);
    glVertex2f(0.15f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(77, 184, 255);
    glVertex2f(0.2f, 0.6f);
    glVertex2f(0.2f, 0.7f);
    glColor3ub(26, 140, 255);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.3f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(77, 184, 255);
    glVertex2f(0.15f, 0.85f);
    glVertex2f(0.15f, 0.95f);
    glColor3ub(26, 140, 255);
    glVertex2f(0.25f, 0.95f);
    glVertex2f(0.25f, 0.85f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(77, 77, 77);
    glVertex2f(-0.1f, 0.5f);
    glVertex2f(-0.1f, 0.65f);
    glVertex2f(0.0f, 0.65f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.03f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(230, 115, 0);
    glVertex2f(0.02f, 0.65f);
    glVertex2f(-0.05f, 0.7f);
    glVertex2f(-0.12f, 0.65f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.15f, 0.85f);
    glVertex2f(0.15f, 0.95f);
    glVertex2f(0.15f, 0.95f);
    glVertex2f(0.25f, 0.95f);
    glVertex2f(0.25f, 0.95f);
    glVertex2f(0.25f, 0.85f);
    glVertex2f(0.25f, 0.85f);
    glVertex2f(0.15f, 0.85f);
    glVertex2f(0.05f, 0.6f);
    glVertex2f(0.05f, 0.7f);
    glVertex2f(0.05f, 0.7f);
    glVertex2f(0.15f, 0.7f);
    glVertex2f(0.15f, 0.7f);
    glVertex2f(0.15f, 0.6f);
    glVertex2f(0.15f, 0.6f);
    glVertex2f(0.05f, 0.6f);
    glVertex2f(0.2f, 0.6f);
    glVertex2f(0.2f, 0.7f);
    glVertex2f(0.2f, 0.7f);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.3f, 0.6f);
    glVertex2f(0.3f, 0.6f);
    glVertex2f(0.2f, 0.6f);
    glColor3ub(255, 153, 51);
    glVertex2f(-0.1f, 0.5f);
    glVertex2f(-0.1f, 0.65f);
    glVertex2f(-0.1f, 0.65f);
    glVertex2f(0.0f, 0.65f);
    glVertex2f(0.0f, 0.65f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.1f, 0.5f);
    glVertex2f(0.02f, 0.65f);
    glVertex2f(-0.05f, 0.7f);
    glVertex2f(-0.05f, 0.7f);
    glVertex2f(-0.12f, 0.65f);
    glVertex2f(-0.12f, 0.65f);
    glVertex2f(0.02f, 0.65f);
    glVertex2f(0.36f, 0.8f);
    glVertex2f(-0.16f, 0.8f);
    glVertex2f(0.36f, 0.84f);
    glVertex2f(-0.16f, 0.84f);
    glVertex2f(-0.14f, 0.8f);
    glVertex2f(-0.14f, 0.84f);
    glVertex2f(-0.1f, 0.8f);
    glVertex2f(-0.1f, 0.84f);
    glVertex2f(-0.05f, 0.8f);
    glVertex2f(-0.05f, 0.84f);
    glVertex2f(-0.0f, 0.8f);
    glVertex2f(-0.0f, 0.84f);
    glVertex2f(0.05f, 0.8f);
    glVertex2f(0.05f, 0.84f);
    glVertex2f(0.1f, 0.8f);
    glVertex2f(0.1f, 0.84f);
    glVertex2f(0.15f, 0.8f);
    glVertex2f(0.15f, 0.84f);
    glVertex2f(0.2f, 0.8f);
    glVertex2f(0.2f, 0.84f);
    glVertex2f(0.25f, 0.8f);
    glVertex2f(0.25f, 0.84f);
    glVertex2f(0.3f, 0.8f);
    glVertex2f(0.3f, 0.84f);
    glVertex2f(0.35f, 0.8f);
    glVertex2f(0.35f, 0.84f);
    glVertex2f(-0.16f, 0.504f);
    glVertex2f(0.36f, 0.504f);
    glVertex2f(-0.16f, 0.5f);
    glVertex2f(0.36f, 0.5f);
    glVertex2f(0.04f, 0.99f);
    glVertex2f(0.36f, 0.99f);
    glVertex2f(0.04f, 0.985f);
    glVertex2f(0.36f, 0.985f);
    glEnd();
}

void factory() {
    glBegin(GL_POLYGON);
    glColor3ub(163, 136, 151);
    glVertex2f(1.5f, -0.8f);
    glVertex2f(1.55f, -0.4f);
    glVertex2f(1.65f, -0.4f);
    glVertex2f(1.7f, -0.8f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(231, 222, 225);
    glVertex2f(1.54f, -0.5f);
    glVertex2f(1.55f, -0.45f);
    glVertex2f(1.65f, -0.45f);
    glVertex2f(1.66f, -0.5f);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(128, 0, 0);
    glVertex2f(1.5f, -0.8f);
    glVertex2f(1.55f, -0.4f);
    glVertex2f(1.55f, -0.4f);
    glVertex2f(1.65f, -0.4f);
    glVertex2f(1.65f, -0.4f);
    glVertex2f(1.7f, -0.8f);
    glVertex2f(1.7f, -0.8f);
    glVertex2f(1.5f, -0.8f);
    glEnd();

    glPushMatrix();
    glTranslatef(position_s, -0.05f, 0.0f);

    x = 0.0f; y = -0.21f; radius = .05f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(217, 217, 217);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = 0.07f; y = -0.25f; radius = .05f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(217, 217, 217);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = 0.0f; y = -0.28f; radius = .05f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(217, 217, 217);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(220, 170, 159);
    glVertex2f(1.45f, -2.0f);
    glVertex2f(1.45f, -0.7f);
    glVertex2f(1.65f, -0.55f);
    glVertex2f(1.65f, -2.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(220, 170, 159);
    glVertex2f(1.65f, -2.0f);
    glVertex2f(1.65f, -0.7f);
    glVertex2f(1.85f, -0.55f);
    glVertex2f(1.85f, -2.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(220, 170, 159);
    glVertex2f(1.85f, -2.0f);
    glVertex2f(1.85f, -0.7f);
    glVertex2f(2.05f, -0.55f);
    glVertex2f(2.05f, -2.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(192, 117, 124);
    glVertex2f(1.45f, -0.7f);
    glVertex2f(1.45f, -0.66f);
    glVertex2f(1.6f, -0.55f);
    glVertex2f(1.65f, -0.55f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(192, 117, 124);
    glVertex2f(1.65f, -0.7f);
    glVertex2f(1.65f, -0.66f);
    glVertex2f(1.8f, -0.55f);
    glVertex2f(1.85f, -0.55f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(192, 117, 124);
    glVertex2f(1.85f, -0.7f);
    glVertex2f(1.85f, -0.66f);
    glVertex2f(2.0f, -0.55f);
    glVertex2f(2.05f, -0.55f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(96, 82, 118);
    glVertex2f(1.5f, -0.78f);
    glVertex2f(1.5f, -0.7f);
    glVertex2f(1.6f, -0.7f);
    glVertex2f(1.6f, -0.78f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(96, 82, 118);
    glVertex2f(1.7f, -0.78f);
    glVertex2f(1.7f, -0.7f);
    glVertex2f(1.8f, -0.7f);
    glVertex2f(1.8f, -0.78f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(96, 82, 118);
    glVertex2f(1.9f, -0.78f);
    glVertex2f(1.9f, -0.7f);
    glVertex2f(1.99f, -0.7f);
    glVertex2f(1.99f, -0.78f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 0, 0);
    glVertex2f(1.45f, -2.0f);
    glVertex2f(1.45f, -0.7f);
    glVertex2f(1.45f, -0.7f);
    glVertex2f(1.65f, -0.55f);
    glVertex2f(1.65f, -0.55f);
    glVertex2f(1.65f, -0.7f);
    glVertex2f(1.65f, -0.7f);
    glVertex2f(1.85f, -0.55f);
    glVertex2f(1.85f, -0.55f);
    glVertex2f(1.85f, -0.7f);
    glVertex2f(1.85f, -0.7f);
    glVertex2f(2.05f, -0.55f);
    glVertex2f(2.05f, -0.55f);
    glVertex2f(2.05f, -0.7f);
    glVertex2f(1.45f, -0.7f);
    glVertex2f(1.45f, -0.66f);
    glVertex2f(1.45f, -0.66f);
    glVertex2f(1.6f, -0.55f);
    glVertex2f(1.6f, -0.55f);
    glVertex2f(1.65f, -0.55f);
    glVertex2f(1.65f, -0.55f);
    glVertex2f(1.45f, -0.7f);
    glVertex2f(1.65f, -0.7f);
    glVertex2f(1.65f, -0.66f);
    glVertex2f(1.65f, -0.66f);
    glVertex2f(1.8f, -0.55f);
    glVertex2f(1.8f, -0.55f);
    glVertex2f(1.85f, -0.55f);
    glVertex2f(1.85f, -0.55f);
    glVertex2f(1.65f, -0.7f);
    glVertex2f(1.85f, -0.7f);
    glVertex2f(1.85f, -0.66f);
    glVertex2f(1.85f, -0.66f);
    glVertex2f(2.0f, -0.55f);
    glVertex2f(2.0f, -0.55f);
    glVertex2f(2.05f, -0.55f);
    glVertex2f(2.05f, -0.55f);
    glVertex2f(1.85f, -0.7f);
    glColor3ub(217, 217, 217);
    glVertex2f(1.5f, -0.78f);
    glVertex2f(1.5f, -0.7f);
    glVertex2f(1.5f, -0.7f);
    glVertex2f(1.6f, -0.7f);
    glVertex2f(1.6f, -0.7f);
    glVertex2f(1.6f, -0.78f);
    glVertex2f(1.6f, -0.78f);
    glVertex2f(1.5f, -0.78f);
    glVertex2f(1.6f, -0.74f);
    glVertex2f(1.5f, -0.74f);
    glVertex2f(1.55f, -0.7f);
    glVertex2f(1.55f, -0.78f);
    glVertex2f(1.7f, -0.78f);
    glVertex2f(1.7f, -0.7f);
    glVertex2f(1.7f, -0.7f);
    glVertex2f(1.8f, -0.7f);
    glVertex2f(1.8f, -0.7f);
    glVertex2f(1.8f, -0.78f);
    glVertex2f(1.8f, -0.78f);
    glVertex2f(1.7f, -0.78f);
    glVertex2f(1.8f, -0.74f);
    glVertex2f(1.7f, -0.74f);
    glVertex2f(1.75f, -0.7f);
    glVertex2f(1.75f, -0.78f);
    glVertex2f(1.9f, -0.78f);
    glVertex2f(1.9f, -0.7f);
    glVertex2f(1.9f, -0.7f);
    glVertex2f(1.99f, -0.7f);
    glVertex2f(1.99f, -0.7f);
    glVertex2f(1.99f, -0.78f);
    glVertex2f(1.99f, -0.78f);
    glVertex2f(1.9f, -0.78f);
    glVertex2f(1.99f, -0.74f);
    glVertex2f(1.9f, -0.74f);
    glVertex2f(1.95f, -0.7f);
    glVertex2f(1.95f, -0.78f);
    glEnd();

    glColor3ub(255, 217, 179);
    c = "F A C T O R Y";
    glRasterPos2f(1.55f, -0.9);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
}

void fence() {
    glBegin(GL_LINES);
    glColor3ub(204, 0, 0);
    glVertex2f(-2.0f, 0.6f);
    glVertex2f(0.39f, 0.6f);
    glVertex2f(-2.0f, 0.53f);
    glVertex2f(0.39f, 0.53f);
    glVertex2f(-1.98f, 0.5f);
    glVertex2f(-1.98f, 0.63f);
    glVertex2f(-1.5f, 0.5f);
    glVertex2f(-1.5f, 0.63f);
    glVertex2f(-1.45f, 0.5f);
    glVertex2f(-1.45f, 0.63f);
    glVertex2f(-0.4f, 0.5f);
    glVertex2f(-0.4f, 0.63f);
    glVertex2f(-0.85f, 0.5f);
    glVertex2f(-0.85f, 0.63f);
    glVertex2f(-0.8f, 0.5f);
    glVertex2f(-0.8f, 0.63f);
    glVertex2f(-0.17f, 0.5f);
    glVertex2f(-0.17f, 0.63f);
    glVertex2f(0.37f, 0.5f);
    glVertex2f(0.37f, 0.63f);
    glVertex2f(2.0f, 0.6f);
    glVertex2f(1.42f, 0.6f);
    glVertex2f(2.0f, 0.53f);
    glVertex2f(1.42f, 0.53f);
    glVertex2f(1.95f, 0.5f);
    glVertex2f(1.95f, 0.63f);
    glVertex2f(1.9f, 0.5f);
    glVertex2f(1.9f, 0.63f);
    glVertex2f(1.85f, 0.5f);
    glVertex2f(1.85f, 0.63f);
    glVertex2f(1.8f, 0.5f);
    glVertex2f(1.8f, 0.63f);
    glVertex2f(1.75f, 0.5f);
    glVertex2f(1.75f, 0.63f);
    glVertex2f(1.7f, 0.5f);
    glVertex2f(1.7f, 0.63f);
    glVertex2f(1.65f, 0.5f);
    glVertex2f(1.65f, 0.63f);
    glVertex2f(1.6f, 0.5f);
    glVertex2f(1.6f, 0.63f);
    glVertex2f(1.55f, 0.5f);
    glVertex2f(1.55f, 0.63f);
    glVertex2f(1.5f, 0.5f);
    glVertex2f(1.5f, 0.63f);
    glVertex2f(1.45f, 0.5f);
    glVertex2f(1.45f, 0.63f);
    glEnd();
}

void road_footpath() {
    glBegin(GL_POLYGON);
    glColor3ub(95, 96, 91);
    glVertex2f(-2.0f, 0.7f);
    glVertex2f(2.0f, 0.7f);
    glVertex2f(2.0f, -0.7f);
    glVertex2f(-2.0f, -0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(95, 96, 91);
    glVertex2f(0.3f, 1.0f);
    glVertex2f(1.5f, 1.0f);
    glVertex2f(1.5f, -1.0f);
    glVertex2f(0.3f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(176, 191, 189);
    glVertex2f(-2.0f, 0.7f);
    glVertex2f(-2.0f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, 0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(176, 191, 189);
    glVertex2f(-2.0f, -0.7f);
    glVertex2f(-2.0f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, -0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(176, 191, 189);
    glVertex2f(2.0f, -0.7f);
    glVertex2f(2.0f, -0.5f);
    glVertex2f(1.3f, -0.5f);
    glVertex2f(1.3f, -0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(176, 191, 189);
    glVertex2f(2.0f, 0.7f);
    glVertex2f(2.0f, 0.5f);
    glVertex2f(1.3f, 0.5f);
    glVertex2f(1.3f, 0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(176, 191, 189);
    glVertex2f(0.3f, -1.0f);
    glVertex2f(0.5f, -1.0f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.3f, -0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(176, 191, 189);
    glVertex2f(1.3f, -1.0f);
    glVertex2f(1.5f, -1.0f);
    glVertex2f(1.5f, -0.5f);
    glVertex2f(1.3f, -0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(176, 191, 189);
    glVertex2f(1.3f, 1.0f);
    glVertex2f(1.5f, 1.0f);
    glVertex2f(1.5f, 0.5f);
    glVertex2f(1.3f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(176, 191, 189);
    glVertex2f(0.3f, 1.0f);
    glVertex2f(0.5f, 1.0f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.3f, 0.5f);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(-2.0f, 0.0f);
    glVertex2f(-1.8f, 0.0f);
    glVertex2f(-1.7f, 0.0f);
    glVertex2f(-1.5f, 0.0f);
    glVertex2f(-1.4f, 0.0f);
    glVertex2f(-1.2f, 0.0f);
    glVertex2f(-1.1f, 0.0f);
    glVertex2f(-0.9f, 0.0f);
    glVertex2f(-0.8f, 0.0f);
    glVertex2f(-0.6f, 0.0f);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(-0.3f, 0.0f);
    glVertex2f(-0.2f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.9f, 0.8f);
    glVertex2f(0.9f, 0.97f);
    glVertex2f(0.9f, -0.97f);
    glVertex2f(0.9f, -0.8f);
    glVertex2f(1.7f, 0.0f);
    glVertex2f(1.9f, 0.0f);
    glEnd();

    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.2f, 0.5f);
    glVertex2f(0.2f, -0.5f);
    glVertex2f(0.4f, -0.5f);
    glVertex2f(0.4f, 0.5f);
    glVertex2f(1.5f, 0.5f);
    glVertex2f(1.5f, -0.5f);
    glVertex2f(1.7f, 0.5f);
    glVertex2f(1.7f, -0.5f);
    glVertex2f(0.5f, 0.7f);
    glVertex2f(1.3f, 0.7f);
    glVertex2f(0.5f, 0.9f);
    glVertex2f(1.3f, 0.9f);
    glVertex2f(0.5f, -0.7f);
    glVertex2f(1.3f, -0.7f);
    glVertex2f(0.5f, -0.9f);
    glVertex2f(1.3f, -0.9f);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(102, 102, 102);
    glVertex2f(-2.0f, 0.7f);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.3f, 1.0f);
    glVertex2f(1.5f, 1.0f);
    glVertex2f(1.5f, 0.7f);
    glVertex2f(1.5f, 0.7f);
    glVertex2f(2.0f, 0.7f);
    glVertex2f(2.0f, -0.7f);
    glVertex2f(1.5f, -0.7f);
    glVertex2f(1.5f, -0.7f);
    glVertex2f(1.5f, -1.0f);
    glVertex2f(0.3f, -1.0f);
    glVertex2f(0.3f, -0.7f);
    glVertex2f(0.3f, -0.7f);
    glVertex2f(-2.0f, -0.7f);
    glEnd();
}

void traffic_light1() {
    glBegin(GL_POLYGON);
    glColor3ub(128, 0, 0);
    glVertex2f(0.55f, 0.38f);
    glVertex2f(0.55f, 0.42f);
    glVertex2f(0.65f, 0.42f);
    glVertex2f(0.65f, 0.38f);
    glEnd();
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(153, 0, 0);
    glVertex2f(0.65f, 0.4f);
    glVertex2f(0.8f, 0.4f);
    glVertex2f(0.8f, 0.4f);
    glVertex2f(0.8f, 0.15f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(204, 122, 0);
    glVertex2f(0.75f, 0.15f);
    glVertex2f(0.85f, 0.15f);
    glVertex2f(0.85f, -0.05f);
    glVertex2f(0.75f, -0.05f);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(0.75f, 0.15f);
    glVertex2f(0.85f, 0.15f);
    glVertex2f(0.85f, 0.15f);
    glVertex2f(0.85f, -0.05f);
    glVertex2f(0.85f, -0.05f);
    glVertex2f(0.75f, -0.05f);
    glVertex2f(0.75f, -0.05f);
    glVertex2f(0.75f, 0.15f);
    glEnd();

    triangleAmount = 50;
    twicePi = 2.0f * PI;
    radius = .025f;
    x = 0.8f; y = 0.1f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(204, 0, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = 0.8f; y = 0.05f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 204, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = 0.8f; y = 0.0f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0, 128, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void traffic_light2() {
    glBegin(GL_POLYGON);
    glColor3ub(128, 0, 0);
    glVertex2f(1.38f, -0.35f);
    glVertex2f(1.42f, -0.35f);
    glVertex2f(1.42f, -0.45f);
    glVertex2f(1.38f, -0.45f);
    glEnd();
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(153, 0, 0);
    glVertex2f(1.4f, -0.35f);
    glVertex2f(1.4f, -0.2f);
    glVertex2f(1.4f, -0.2f);
    glVertex2f(1.1f, -0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(204, 122, 0);
    glVertex2f(1.0f, -0.1f);
    glVertex2f(1.1f, -0.1f);
    glVertex2f(1.1f, -0.3f);
    glVertex2f(1.0f, -0.3f);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(1.0f, -0.1f);
    glVertex2f(1.1f, -0.1f);
    glVertex2f(1.1f, -0.1f);
    glVertex2f(1.1f, -0.3f);
    glVertex2f(1.1f, -0.3f);
    glVertex2f(1.0f, -0.3f);
    glVertex2f(1.0f, -0.3f);
    glVertex2f(1.0f, -0.1f);
    glEnd();

    triangleAmount = 50;
    twicePi = 2.0f * PI;
    radius = .025f;
    x = 1.05f; y = -0.15f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(204, 0, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = 1.05f; y = -0.2f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 204, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = 1.05f; y = -0.25f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0, 128, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void road_light() {
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(-1.9f, 0.45f);
    glVertex2f(-1.8f, 0.45f);
    glVertex2f(-1.8f, 0.45f);
    glVertex2f(-1.8f, 0.15f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(191, 191, 191);
    glVertex2f(-1.85f, 0.28f);
    glVertex2f(-1.8f, 0.28f);
    glVertex2f(-1.8f, 0.15f);
    glVertex2f(-1.85f, 0.15f);
    glEnd();
    glPointSize(8.0);
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(-1.9f, 0.45f);
    glEnd();

    for (int i = 0; i < 3; i++) {
        glTranslated(0.6, 0.0, 0.0);
        glBegin(GL_LINES);
        glColor3ub(128, 128, 128);
        glVertex2f(-1.9f, 0.45f);
        glVertex2f(-1.8f, 0.45f);
        glVertex2f(-1.8f, 0.45f);
        glVertex2f(-1.8f, 0.15f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(191, 191, 191);
        glVertex2f(-1.85f, 0.28f);
        glVertex2f(-1.8f, 0.28f);
        glVertex2f(-1.8f, 0.15f);
        glVertex2f(-1.85f, 0.15f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3ub(89, 89, 89);
        glVertex2f(-1.9f, 0.45f);
        glEnd();
    }

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(-1.6f, -0.45f);
    glVertex2f(-1.5f, -0.45f);
    glVertex2f(-1.5f, -0.45f);
    glVertex2f(-1.5f, -0.15f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(191, 191, 191);
    glVertex2f(-1.5f, -0.15f);
    glVertex2f(-1.55f, -0.15f);
    glVertex2f(-1.55f, -0.28f);
    glVertex2f(-1.5f, -0.28f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(-1.6f, -0.45f);
    glEnd();

    for (int i = 0; i < 3; i++) {
        glTranslated(-0.6, 0.0, 0.0);
        glBegin(GL_LINES);
        glColor3ub(128, 128, 128);
        glVertex2f(-1.6f, -0.45f);
        glVertex2f(-1.5f, -0.45f);
        glVertex2f(-1.5f, -0.45f);
        glVertex2f(-1.5f, -0.15f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(191, 191, 191);
        glVertex2f(-1.5f, -0.15f);
        glVertex2f(-1.55f, -0.15f);
        glVertex2f(-1.55f, -0.28f);
        glVertex2f(-1.5f, -0.28f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3ub(89, 89, 89);
        glVertex2f(-1.6f, -0.45f);
        glEnd();
    }

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(1.4f, 0.45f);
    glVertex2f(1.5f, 0.45f);
    glVertex2f(1.5f, 0.45f);
    glVertex2f(1.5f, 0.15f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(191, 191, 191);
    glVertex2f(1.5f, 0.15f);
    glVertex2f(1.45f, 0.15f);
    glVertex2f(1.45f, 0.28f);
    glVertex2f(1.5f, 0.28f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(1.4f, 0.45f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(1.7f, -0.45f);
    glVertex2f(1.8f, -0.45f);
    glVertex2f(1.8f, -0.45f);
    glVertex2f(1.8f, -0.15f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(191, 191, 191);
    glVertex2f(1.8f, -0.15f);
    glVertex2f(1.75f, -0.15f);
    glVertex2f(1.75f, -0.28f);
    glVertex2f(1.8f, -0.28f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(1.7f, -0.45f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(0.55f, -0.7f);
    glVertex2f(0.55f, -0.6f);
    glVertex2f(0.55f, -0.6f);
    glVertex2f(0.75f, -0.6f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(191, 191, 191);
    glVertex2f(0.75f, -0.6f);
    glVertex2f(0.75f, -0.65f);
    glVertex2f(0.62f, -0.65f);
    glVertex2f(0.62f, -0.6f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(0.55f, -0.7f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(1.25f, -0.7f);
    glVertex2f(1.25f, -0.6f);
    glVertex2f(1.25f, -0.6f);
    glVertex2f(1.05f, -0.6f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(191, 191, 191);
    glVertex2f(1.05f, -0.6f);
    glVertex2f(1.05f, -0.65f);
    glVertex2f(1.18f, -0.65f);
    glVertex2f(1.18f, -0.6f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(1.25f, -0.7f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(0.55f, 0.7f);
    glVertex2f(0.55f, 0.8f);
    glVertex2f(0.55f, 0.8f);
    glVertex2f(0.75f, 0.8f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(191, 191, 191);
    glVertex2f(0.75f, 0.8f);
    glVertex2f(0.75f, 0.75f);
    glVertex2f(0.62f, 0.75f);
    glVertex2f(0.62f, 0.8f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(0.55f, 0.7f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(1.25f, 0.7f);
    glVertex2f(1.25f, 0.8f);
    glVertex2f(1.25f, 0.8f);
    glVertex2f(1.05f, 0.8f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(191, 191, 191);
    glVertex2f(1.05f, 0.8f);
    glVertex2f(1.05f, 0.75f);
    glVertex2f(1.18f, 0.75f);
    glVertex2f(1.18f, 0.8f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(1.25f, 0.7f);
    glEnd();
}

// ==================== BOATS ====================

void boat1() {
    glPushMatrix();
    glTranslatef(position_b1, -0.75f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(255, 140, 26);
    glVertex2f(-0.05f, -0.05f);
    glVertex2f(-0.05f, -0.1f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, -0.05f);
    glEnd();

    x = 0.1f; y = -0.1f; radius = .05f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(255, 140, 26);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    x = -0.05f; y = -0.1f; radius = .05f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(179, 89, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(102, 51, 0);
    glVertex2f(-0.25f, -0.1f);
    glVertex2f(0.25f, -0.1f);
    glVertex2f(0.15f, -0.15f);
    glVertex2f(-0.15f, -0.15f);
    glEnd();
    glPopMatrix();
}

void boat2() {
    glPushMatrix();
    glTranslatef(position_b2, -0.65f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(230, 230, 0);
    glVertex2f(-0.05f, -0.05f);
    glVertex2f(-0.05f, -0.1f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, -0.05f);
    glEnd();

    x = 0.1f; y = -0.1f; radius = .05f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(153, 153, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    x = -0.05f; y = -0.1f; radius = .05f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(230, 230, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.25f, -0.1f);
    glVertex2f(0.25f, -0.1f);
    glVertex2f(0.15f, -0.15f);
    glVertex2f(-0.15f, -0.15f);
    glEnd();
    glPopMatrix();
}

void boat1_shore() {
    glPushMatrix();
    glTranslatef(-1.85f, -0.75f, 0.0f);
    glBegin(GL_POLYGON);
    glColor3ub(255, 140, 26);
    glVertex2f(-0.05f, -0.05f);
    glVertex2f(-0.05f, -0.1f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, -0.05f);
    glEnd();
    x = 0.1f; y = -0.1f; radius = .05f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(255, 140, 26);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = -0.05f; y = -0.1f; radius = .05f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(179, 89, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(102, 51, 0);
    glVertex2f(-0.25f, -0.1f);
    glVertex2f(0.25f, -0.1f);
    glVertex2f(0.15f, -0.15f);
    glVertex2f(-0.15f, -0.15f);
    glEnd();
    glPopMatrix();
}

void boat2_shore() {
    glPushMatrix();
    glTranslatef(-1.55f, -0.65f, 0.0f);
    glBegin(GL_POLYGON);
    glColor3ub(230, 230, 0);
    glVertex2f(-0.05f, -0.05f);
    glVertex2f(-0.05f, -0.1f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, -0.05f);
    glEnd();
    x = 0.1f; y = -0.1f; radius = .05f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(153, 153, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = -0.05f; y = -0.1f; radius = .05f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(230, 230, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.25f, -0.1f);
    glVertex2f(0.25f, -0.1f);
    glVertex2f(0.15f, -0.15f);
    glVertex2f(-0.15f, -0.15f);
    glEnd();
    glPopMatrix();
}

// ==================== EXTRA CARS ====================

void car1_extra() {
    glPushMatrix();
    glTranslatef(position_c1_extra, -0.18f, 0.0f);
    glBegin(GL_POLYGON);
    glColor3ub(200, 100, 0);
    glVertex2f(-0.2f, 0.25f);
    glVertex2f(0.07f, 0.25f);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.15f, 0.07f);
    glVertex2f(0.07f, 0.05f);
    glVertex2f(-0.2f, 0.05f);
    glVertex2f(-0.22f, 0.07f);
    glVertex2f(-0.22f, 0.23f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.18f, 0.06f);
    glVertex2f(-0.18f, 0.24f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(200, 100, 0);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(-0.15f, 0.21f);
    glVertex2f(-0.15f, 0.09f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(200, 100, 0);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.18f, 0.06f);
    glVertex2f(-0.15f, 0.09f);
    glVertex2f(-0.15f, 0.21f);
    glVertex2f(-0.18f, 0.24f);
    glEnd();
    glPopMatrix();
}

void car2_extra() {
    glPushMatrix();
    glTranslatef(position_c2_extra, 0.0f, 0.0f);
    glRotatef(180, 0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glColor3ub(0, 200, 100);
    glVertex2f(-0.04f, 0.25f);
    glVertex2f(0.07f, 0.25f);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.15f, 0.07f);
    glVertex2f(0.07f, 0.05f);
    glVertex2f(-0.04f, 0.05f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.03f, 0.06f);
    glVertex2f(-0.03f, 0.24f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(0, 200, 100);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(-0.07f, 0.21f);
    glVertex2f(-0.07f, 0.09f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(0, 200, 100);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.03f, 0.24f);
    glVertex2f(-0.03f, 0.21f);
    glVertex2f(-0.03f, 0.09f);
    glVertex2f(-0.03f, 0.06f);
    glEnd();
    glPopMatrix();
}

void car3_extra() {
    glPushMatrix();
    glTranslatef(0.75f, position_c3_extra, 0.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glColor3ub(200, 200, 0);
    glVertex2f(-0.13f, 0.25f);
    glVertex2f(0.07f, 0.25f);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.15f, 0.07f);
    glVertex2f(0.07f, 0.05f);
    glVertex2f(-0.13f, 0.05f);
    glVertex2f(-0.15f, 0.07f);
    glVertex2f(-0.15f, 0.23f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.13f, 0.06f);
    glVertex2f(-0.13f, 0.24f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(200, 200, 0);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(-0.1f, 0.21f);
    glVertex2f(-0.1f, 0.09f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(200, 200, 0);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.13f, 0.06f);
    glVertex2f(-0.1f, 0.09f);
    glVertex2f(-0.1f, 0.21f);
    glVertex2f(-0.13f, 0.24f);
    glEnd();
    glPopMatrix();
}

void car4_extra() {
    glPushMatrix();
    glTranslatef(0.95f, position_c4_extra, 0.0f);
    glRotatef(270, 0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glColor3ub(0, 200, 200);
    glVertex2f(-0.13f, 0.25f);
    glVertex2f(0.07f, 0.25f);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.15f, 0.07f);
    glVertex2f(0.07f, 0.05f);
    glVertex2f(-0.13f, 0.05f);
    glVertex2f(-0.15f, 0.07f);
    glVertex2f(-0.15f, 0.23f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.13f, 0.06f);
    glVertex2f(-0.13f, 0.24f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(0, 200, 200);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(-0.1f, 0.21f);
    glVertex2f(-0.1f, 0.09f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(0, 200, 200);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.13f, 0.06f);
    glVertex2f(-0.1f, 0.09f);
    glVertex2f(-0.1f, 0.21f);
    glVertex2f(-0.13f, 0.24f);
    glEnd();
    glPopMatrix();
}

// ==================== MAIN CAR FUNCTIONS ====================

void car1() {
    glPushMatrix();
    float shiftLimit = 0.25f;
    float actualShift = car1_shift;
    if (actualShift > shiftLimit) actualShift = shiftLimit;
    glTranslatef(position_c1, actualShift, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(230, 0, 0);
    glVertex2f(-0.2f, 0.25f);
    glVertex2f(0.07f, 0.25f);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.15f, 0.07f);
    glVertex2f(0.07f, 0.05f);
    glVertex2f(-0.2f, 0.05f);
    glVertex2f(-0.22f, 0.07f);
    glVertex2f(-0.22f, 0.23f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.18f, 0.06f);
    glVertex2f(-0.18f, 0.24f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(230, 0, 0);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(-0.15f, 0.21f);
    glVertex2f(-0.15f, 0.09f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(242, 242, 242);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.14f, 0.2f);
    glVertex2f(0.14f, 0.23f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(242, 242, 242);
    glVertex2f(0.15f, 0.07f);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.14f, 0.1f);
    glVertex2f(0.14f, 0.07f);
    glEnd();

    if (flag != 0) {
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 170);
        glVertex2f(0.17f, 0.21f);
        glVertex2f(0.14f, 0.25f);
        glVertex2f(0.6f, 0.34f);
        glVertex2f(0.6f, 0.06f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 170);
        glVertex2f(0.17f, 0.09f);
        glVertex2f(0.14f, 0.05f);
        glVertex2f(0.6f, -0.04f);
        glVertex2f(0.6f, 0.24f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2f(0.17f, 0.2f);
        glVertex2f(0.14f, 0.23f);
        glVertex2f(0.5f, 0.3f);
        glVertex2f(0.5f, 0.1f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2f(0.17f, 0.1f);
        glVertex2f(0.14f, 0.07f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.5f, 0.2f);
        glEnd();
    }

    glBegin(GL_LINES);
    glColor3ub(230, 0, 0);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.18f, 0.06f);
    glVertex2f(-0.15f, 0.09f);
    glVertex2f(-0.15f, 0.21f);
    glVertex2f(-0.18f, 0.24f);
    glVertex2f(-0.06f, 0.24f);
    glVertex2f(-0.06f, 0.21f);
    glVertex2f(-0.06f, 0.09f);
    glVertex2f(-0.06f, 0.06f);
    glEnd();
    glPopMatrix();
}

void car2() {
    glPushMatrix();
    glTranslatef(position_c2, 0.0f, 0.0f);
    glRotatef(180, 0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glColor3ub(255, 204, 0);
    glVertex2f(-0.04f, 0.25f);
    glVertex2f(0.07f, 0.25f);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.15f, 0.07f);
    glVertex2f(0.07f, 0.05f);
    glVertex2f(-0.04f, 0.05f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.03f, 0.06f);
    glVertex2f(-0.03f, 0.24f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 204, 0);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(-0.07f, 0.21f);
    glVertex2f(-0.07f, 0.09f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(242, 242, 242);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.14f, 0.2f);
    glVertex2f(0.14f, 0.23f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(242, 242, 242);
    glVertex2f(0.15f, 0.07f);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.14f, 0.1f);
    glVertex2f(0.14f, 0.07f);
    glEnd();

    if (flag != 0) {
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 170);
        glVertex2f(0.17f, 0.21f);
        glVertex2f(0.14f, 0.25f);
        glVertex2f(0.6f, 0.34f);
        glVertex2f(0.6f, 0.06f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 170);
        glVertex2f(0.17f, 0.09f);
        glVertex2f(0.14f, 0.05f);
        glVertex2f(0.6f, -0.04f);
        glVertex2f(0.6f, 0.24f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2f(0.17f, 0.2f);
        glVertex2f(0.14f, 0.23f);
        glVertex2f(0.5f, 0.3f);
        glVertex2f(0.5f, 0.1f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2f(0.17f, 0.1f);
        glVertex2f(0.14f, 0.07f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.5f, 0.2f);
        glEnd();
    }

    glBegin(GL_POLYGON);
    glColor3ub(242, 242, 242);
    glVertex2f(-0.06f, 0.25f);
    glVertex2f(-0.06f, 0.05f);
    glVertex2f(-0.5f, 0.05f);
    glVertex2f(-0.5f, 0.25f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 204, 0);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.03f, 0.24f);
    glVertex2f(-0.03f, 0.21f);
    glVertex2f(-0.03f, 0.09f);
    glVertex2f(-0.03f, 0.06f);
    glColor3ub(217, 217, 217);
    glVertex2f(-0.06f, 0.25f);
    glVertex2f(-0.06f, 0.05f);
    glVertex2f(-0.06f, 0.05f);
    glVertex2f(-0.5f, 0.05f);
    glVertex2f(-0.5f, 0.05f);
    glVertex2f(-0.5f, 0.25f);
    glVertex2f(-0.5f, 0.25f);
    glVertex2f(-0.06f, 0.25f);
    glEnd();
    glPopMatrix();
}

void car3() {
    glPushMatrix();
    float shiftLimit = 0.95f;   // was 0.2f – now allows full right‑lane movement
    float actualShift = car3_shift;
    if (actualShift < -shiftLimit) actualShift = -shiftLimit;
    glTranslatef(0.75f + actualShift, position_c3, 0.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-0.13f, 0.25f);
    glVertex2f(0.07f, 0.25f);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.15f, 0.07f);
    glVertex2f(0.07f, 0.05f);
    glVertex2f(-0.13f, 0.05f);
    glVertex2f(-0.15f, 0.07f);
    glVertex2f(-0.15f, 0.23f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.13f, 0.06f);
    glVertex2f(-0.13f, 0.24f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(-0.1f, 0.21f);
    glVertex2f(-0.1f, 0.09f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(242, 242, 242);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.14f, 0.2f);
    glVertex2f(0.14f, 0.23f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(242, 242, 242);
    glVertex2f(0.15f, 0.07f);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.14f, 0.1f);
    glVertex2f(0.14f, 0.07f);
    glEnd();

    if (flag != 0) {
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 170);
        glVertex2f(0.17f, 0.21f);
        glVertex2f(0.14f, 0.25f);
        glVertex2f(0.6f, 0.34f);
        glVertex2f(0.6f, 0.06f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 170);
        glVertex2f(0.17f, 0.09f);
        glVertex2f(0.14f, 0.05f);
        glVertex2f(0.6f, -0.04f);
        glVertex2f(0.6f, 0.24f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2f(0.17f, 0.2f);
        glVertex2f(0.14f, 0.23f);
        glVertex2f(0.5f, 0.3f);
        glVertex2f(0.5f, 0.1f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2f(0.17f, 0.1f);
        glVertex2f(0.14f, 0.07f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.5f, 0.2f);
        glEnd();
    }

    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.13f, 0.06f);
    glVertex2f(-0.1f, 0.09f);
    glVertex2f(-0.1f, 0.21f);
    glVertex2f(-0.13f, 0.24f);
    glVertex2f(-0.03f, 0.24f);
    glVertex2f(-0.03f, 0.21f);
    glVertex2f(-0.03f, 0.09f);
    glVertex2f(-0.03f, 0.06f);
    glEnd();
    glPopMatrix();
}

void car4() {
    glPushMatrix();
    float shiftLimit = 0.2f;
    float actualShift = car4_shift;
    if (actualShift > shiftLimit) actualShift = shiftLimit;
    glTranslatef(0.95f + actualShift, position_c4, 0.0f);
    glRotatef(270, 0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glColor3ub(51, 102, 255);
    glVertex2f(-0.13f, 0.25f);
    glVertex2f(0.07f, 0.25f);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.15f, 0.07f);
    glVertex2f(0.07f, 0.05f);
    glVertex2f(-0.13f, 0.05f);
    glVertex2f(-0.15f, 0.07f);
    glVertex2f(-0.15f, 0.23f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.13f, 0.06f);
    glVertex2f(-0.13f, 0.24f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(51, 102, 255);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(-0.1f, 0.21f);
    glVertex2f(-0.1f, 0.09f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(242, 242, 242);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.17f, 0.2f);
    glVertex2f(0.14f, 0.2f);
    glVertex2f(0.14f, 0.23f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(242, 242, 242);
    glVertex2f(0.15f, 0.07f);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.14f, 0.1f);
    glVertex2f(0.14f, 0.07f);
    glEnd();

    if (flag != 0) {
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 170);
        glVertex2f(0.17f, 0.21f);
        glVertex2f(0.14f, 0.25f);
        glVertex2f(0.6f, 0.34f);
        glVertex2f(0.6f, 0.06f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 170);
        glVertex2f(0.17f, 0.09f);
        glVertex2f(0.14f, 0.05f);
        glVertex2f(0.6f, -0.04f);
        glVertex2f(0.6f, 0.24f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2f(0.17f, 0.2f);
        glVertex2f(0.14f, 0.23f);
        glVertex2f(0.5f, 0.3f);
        glVertex2f(0.5f, 0.1f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2f(0.17f, 0.1f);
        glVertex2f(0.14f, 0.07f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.5f, 0.2f);
        glEnd();
    }

    glBegin(GL_LINES);
    glColor3ub(51, 102, 255);
    glVertex2f(0.07f, 0.24f);
    glVertex2f(0.03f, 0.21f);
    glVertex2f(0.03f, 0.09f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.13f, 0.06f);
    glVertex2f(-0.1f, 0.09f);
    glVertex2f(-0.1f, 0.21f);
    glVertex2f(-0.13f, 0.24f);
    glVertex2f(-0.03f, 0.24f);
    glVertex2f(-0.03f, 0.21f);
    glVertex2f(-0.03f, 0.09f);
    glVertex2f(-0.03f, 0.06f);
    glEnd();
    glPopMatrix();
}

void river() {
    glBegin(GL_POLYGON);
    glColor3ub(51, 204, 255);
    glVertex2f(-2.0f, -1.0f);
    glVertex2f(-2.0f, -0.55f);
    glVertex2f(0.15f, -0.55f);
    glVertex2f(0.15f, -1.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(position_r, 0.0f, 0.0f);

    for (float waveY = -0.95f; waveY <= -0.6f; waveY += 0.08f) {
        for (float waveX = -1.9f; waveX <= 0.1f; waveX += 0.15f) {
            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(0, 191, 255);
            x = waveX; y = waveY; radius = 0.04f;
            glVertex2f(x, y);
            for (int i = 0; i <= triangleAmount;i++) {
                glVertex2f(
                    x + (radius * cos(i * twicePi / triangleAmount)),
                    y + (radius * sin(i * twicePi / triangleAmount))
                );
            }
            glEnd();
        }
    }

    glPopMatrix();
}

// ==================== TRAFFIC SIGNAL CONTROL ====================

void redgreen1() {
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    radius = .025f;

    x = 0.8f; y = 0.1f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 51, 51);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    x = 0.8f; y = 0.0f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0, 50, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    x = 1.05f; y = -0.15f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(50, 0, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    x = 1.05f; y = -0.25f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0, 255, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void redgreen2() {
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    radius = .025f;

    x = 0.8f; y = 0.1f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(50, 0, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    x = 0.8f; y = 0.0f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0, 255, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    x = 1.05f; y = -0.15f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 51, 51);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    x = 1.05f; y = -0.25f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0, 50, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

// ========== EMERGENCY - HORIZONTAL GREEN, VERTICAL RED ==========
void redgreen_emergency() {
    int flashOn = (frameNumber / 5) % 2;

    triangleAmount = 50;
    twicePi = 2.0f * PI;
    radius = .025f;

    // Horizontal: RED OFF, GREEN ON
    x = 0.8f; y = 0.1f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(50, 0, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    x = 0.8f; y = 0.0f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0, 255, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    // Vertical: RED ON, GREEN OFF
    x = 1.05f; y = -0.15f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 51, 51);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    x = 1.05f; y = -0.25f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0, 50, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    // Yellow lights OFF
    x = 0.8f; y = 0.05f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(80, 80, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    x = 1.05f; y = -0.2f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(80, 80, 0);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    if (flashOn) glColor3ub(255, 0, 0);
    else glColor3ub(255, 255, 0);

    const char* msg;
    if (ambulanceOn && firetruckOn)
        msg = "!! EMERGENCY VEHICLES - HORIZONTAL GREEN, VERTICAL RED !!";
    else if (ambulanceOn)
        msg = "!! AMBULANCE - HORIZONTAL GREEN, VERTICAL RED !!";
    else
        msg = "!! FIRE TRUCK - HORIZONTAL GREEN, VERTICAL RED !!";

    glRasterPos2f(-0.9f, 0.95f);
    for (int i = 0; msg[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg[i]);
}

// ==================== EMERGENCY VEHICLES ====================

void ambulance() {
    glPushMatrix();
    glTranslatef(position_amb, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-0.25f, 0.27f);
    glVertex2f(0.10f, 0.27f);
    glVertex2f(0.18f, 0.24f);
    glVertex2f(0.20f, 0.20f);
    glVertex2f(0.20f, 0.05f);
    glVertex2f(0.18f, 0.02f);
    glVertex2f(0.10f, 0.0f);
    glVertex2f(-0.25f, 0.0f);
    glVertex2f(-0.27f, 0.02f);
    glVertex2f(-0.27f, 0.24f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(204, 0, 0);
    glVertex2f(-0.27f, 0.13f);
    glVertex2f(0.20f, 0.13f);
    glVertex2f(0.20f, 0.085f);
    glVertex2f(-0.27f, 0.085f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(153, 217, 234);
    glVertex2f(0.10f, 0.25f);
    glVertex2f(0.10f, 0.135f);
    glVertex2f(-0.05f, 0.135f);
    glVertex2f(-0.05f, 0.25f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex2f(-0.16f, 0.105f);
    glVertex2f(-0.10f, 0.105f);
    glVertex2f(-0.10f, 0.225f);
    glVertex2f(-0.16f, 0.225f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex2f(-0.205f, 0.145f);
    glVertex2f(-0.065f, 0.145f);
    glVertex2f(-0.065f, 0.185f);
    glVertex2f(-0.205f, 0.185f);
    glEnd();

    triangleAmount = 30;
    twicePi = 2.0f * PI;
    radius = 0.035f;
    glColor3ub(26, 26, 26);
    x = -0.16f; y = -0.02f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
    x = 0.08f; y = -0.02f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    int flashOn = (frameNumber / 8) % 2;
    glBegin(GL_POLYGON);
    if (flashOn) glColor3ub(255, 0, 0); else glColor3ub(80, 0, 0);
    glVertex2f(-0.07f, 0.27f);
    glVertex2f(0.0f, 0.27f);
    glVertex2f(0.0f, 0.32f);
    glVertex2f(-0.07f, 0.32f);
    glEnd();

    glBegin(GL_POLYGON);
    if (flashOn) glColor3ub(60, 60, 255); else glColor3ub(0, 0, 90);
    glVertex2f(0.0f, 0.27f);
    glVertex2f(0.07f, 0.27f);
    glVertex2f(0.07f, 0.32f);
    glVertex2f(0.0f, 0.32f);
    glEnd();

    if (flag != 0) {
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 170);
        glVertex2f(0.20f, 0.20f);
        glVertex2f(0.18f, 0.24f);
        glVertex2f(0.62f, 0.32f);
        glVertex2f(0.62f, 0.04f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2f(0.20f, 0.18f);
        glVertex2f(0.18f, 0.21f);
        glVertex2f(0.52f, 0.28f);
        glVertex2f(0.52f, 0.08f);
        glEnd();
    }

    glPopMatrix();
}

void firetruck() {
    glPushMatrix();
    glTranslatef(0.75f, position_fire, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(204, 0, 0);
    glVertex2f(-0.10f, -0.25f);
    glVertex2f(0.10f, -0.25f);
    glVertex2f(0.11f, -0.18f);
    glVertex2f(0.11f, 0.18f);
    glVertex2f(0.10f, 0.25f);
    glVertex2f(-0.10f, 0.25f);
    glVertex2f(-0.11f, 0.18f);
    glVertex2f(-0.11f, -0.18f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(153, 217, 234);
    glVertex2f(-0.07f, 0.10f);
    glVertex2f(0.07f, 0.10f);
    glVertex2f(0.07f, 0.22f);
    glVertex2f(-0.07f, 0.22f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-0.11f, -0.02f);
    glVertex2f(0.11f, -0.02f);
    glVertex2f(0.11f, -0.07f);
    glVertex2f(-0.11f, -0.07f);
    glEnd();

    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 0);
    glVertex2f(-0.08f, -0.22f); glVertex2f(0.08f, -0.10f);
    glVertex2f(0.08f, -0.22f); glVertex2f(-0.08f, -0.10f);
    glVertex2f(-0.08f, -0.16f); glVertex2f(0.08f, -0.16f);
    glVertex2f(-0.08f, -0.22f); glVertex2f(-0.08f, -0.10f);
    glVertex2f(0.08f, -0.22f); glVertex2f(0.08f, -0.10f);
    glEnd();

    triangleAmount = 30;
    twicePi = 2.0f * PI;
    radius = 0.035f;
    glColor3ub(26, 26, 26);
    x = -0.06f; y = -0.25f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
    x = 0.06f; y = -0.25f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    int flashOn = (frameNumber / 8) % 2;
    glBegin(GL_POLYGON);
    if (flashOn) glColor3ub(255, 0, 0); else glColor3ub(80, 0, 0);
    glVertex2f(-0.07f, 0.22f);
    glVertex2f(0.0f, 0.22f);
    glVertex2f(0.0f, 0.28f);
    glVertex2f(-0.07f, 0.28f);
    glEnd();

    glBegin(GL_POLYGON);
    if (flashOn) glColor3ub(255, 255, 255); else glColor3ub(120, 120, 120);
    glVertex2f(0.0f, 0.22f);
    glVertex2f(0.07f, 0.22f);
    glVertex2f(0.07f, 0.28f);
    glVertex2f(0.0f, 0.28f);
    glEnd();

    if (flag != 0) {
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 170);
        glVertex2f(-0.11f, 0.24f);
        glVertex2f(0.11f, 0.24f);
        glVertex2f(0.30f, 0.65f);
        glVertex2f(-0.30f, 0.65f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2f(-0.08f, 0.24f);
        glVertex2f(0.08f, 0.24f);
        glVertex2f(0.18f, 0.50f);
        glVertex2f(-0.18f, 0.50f);
        glEnd();
    }

    glPopMatrix();
}

// ==================== RAIN ====================

void rain() {
    glPushMatrix();
    glTranslatef(position_rain2, position_rain, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.0f, 0.9f);
    glVertex2f(0.05f, 0.85f);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.0f, 0.7f);
    glVertex2f(0.05f, 0.65f);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.05f, 0.45f);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.0f, 0.3f);
    glVertex2f(0.05f, 0.25f);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.0f, 0.1f);
    glVertex2f(0.05f, 0.05f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.05f, -0.9f);
    glVertex2f(0.0f, -0.85f);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.05f, -0.7f);
    glVertex2f(0.0f, -0.65f);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.05f, -0.5f);
    glVertex2f(0.0f, -0.45f);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.05f, -0.3f);
    glVertex2f(0.0f, -0.25f);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.05f, -0.1f);
    glVertex2f(0.0f, -0.05f);
    glEnd();

    for (int i = 0; i < 100; i++) {
        glTranslatef(-0.2, 0.0, 0.0f);
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.0f, 0.9f);
        glVertex2f(0.05f, 0.85f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.0f, 0.7f);
        glVertex2f(0.05f, 0.65f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.05f, 0.45f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.05f, 0.25f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.05f, 0.05f);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.05f, -0.9f);
        glVertex2f(0.0f, -0.85f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.0f, -0.65f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.05f, -0.5f);
        glVertex2f(0.0f, -0.45f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.05f, -0.3f);
        glVertex2f(0.0f, -0.25f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.05f, -0.1f);
        glVertex2f(0.0f, -0.05f);
        glEnd();
    }

    for (int i = 0; i < 100; i++) {
        glTranslatef(0.2, 0.0, 0.0f);
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.0f, 0.9f);
        glVertex2f(0.05f, 0.85f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.0f, 0.7f);
        glVertex2f(0.05f, 0.65f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.05f, 0.45f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.05f, 0.25f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.05f, 0.05f);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.05f, -0.9f);
        glVertex2f(0.0f, -0.85f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.0f, -0.65f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.05f, -0.5f);
        glVertex2f(0.0f, -0.45f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.05f, -0.3f);
        glVertex2f(0.0f, -0.25f);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.05f, -0.1f);
        glVertex2f(0.0f, -0.05f);
        glEnd();
    }
    glPopMatrix();
}

// ==================== DISPLAY FUNCTIONS ====================

void start() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);
    glVertex2f(-2.0f, 2.0f);
    glColor3ub(147, 112, 219);
    glVertex2f(2.0f, 2.0f);
    glColor3ub(30, 144, 255);
    glVertex2f(2.0f, -2.0f);
    glColor3ub(70, 130, 180);
    glVertex2f(-2.0f, -2.0f);
    glEnd();

    glColor3ub(255, 255, 255);
    c = "Smart City Adaptive Traffic Management System";
    glRasterPos2f(-0.8, 0.8);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    glColor3ub(0, 0, 0);
    float yPos = 0.5f;
    c = "Controls:";
    glRasterPos2f(-1.0, yPos);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    yPos -= 0.08f;
    c = "F - Start Simulation";
    glRasterPos2f(-1.0, yPos);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    yPos -= 0.08f;
    c = "R - Manual: Red Horizontal, Green Vertical";
    glRasterPos2f(-1.0, yPos);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    yPos -= 0.08f;
    c = "G - Manual: Green Horizontal, Red Vertical";
    glRasterPos2f(-1.0, yPos);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    yPos -= 0.08f;
    glColor3ub(255, 0, 0);
    c = "C - CONGESTION on Road 1 -> Road 2 gets RED signal";
    glRasterPos2f(-1.0, yPos);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    yPos -= 0.08f;
    c = "V - CONGESTION on Road 2 -> Road 1 gets RED signal";
    glRasterPos2f(-1.0, yPos);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    yPos -= 0.08f;
    c = "A - Toggle Ambulance (EMERGENCY PRIORITY)";
    glRasterPos2f(-1.0, yPos);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    yPos -= 0.08f;
    c = "T - Toggle Fire Truck (EMERGENCY PRIORITY)";
    glRasterPos2f(-1.0, yPos);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    yPos -= 0.08f;
    c = "D - Day Mode | N - Night Mode";
    glRasterPos2f(-1.0, yPos);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    yPos -= 0.08f;
    c = "LMB - Start Rain | RMB - Stop Rain";
    glRasterPos2f(-1.0, yPos);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    yPos -= 0.15f;
    glColor3ub(0, 0, 255);
    c = "EMERGENCY: Ambulance/Fire Truck -> HORIZONTAL GREEN, VERTICAL RED";
    glRasterPos2f(-0.7, yPos);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    glFlush();
}


// -------- Modified day() and night() --------
void day() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3ub(51, 204, 51);
    glVertex2f(2.0f, 1.0f);
    glVertex2f(2.0f, -1.0f);
    glVertex2f(-2.0f, -1.0f);
    glVertex2f(-2.0f, 1.0f);
    glEnd();

    river();
    glBegin(GL_POLYGON);
    glColor3ub(51, 204, 51);
    glVertex2f(0.35f, -0.5f);
    glVertex2f(1.9f, -0.5f);
    glVertex2f(1.9f, -1.0f);
    glVertex2f(0.35f, -1.0f);
    glEnd();

    tree();
    road_footpath();
    car1();
    car2();
    car3();
    car4();

    if (extraCarsOnRoad1 == 1) {
        car1_extra();
        car2_extra();
    }
    if (extraCarsOnRoad2 == 1) {
        car3_extra();
        car4_extra();
    }

    // Show only the active vehicle when alternating
    if (!alternatingMode || currentVehicle == 0) ambulance();
    if (!alternatingMode || currentVehicle == 1) firetruck();

    traffic_light1();
    traffic_light2();
    road_light();
    factory();

    glPushMatrix();
    windmill();
    glPopMatrix();

    fence();
    shop();
    house();
    boat1();
    boat2();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 204);
    glVertex2f(-1.72f, 0.57f);
    glVertex2f(-1.72f, 0.6f);
    glVertex2f(-1.65f, 0.6f);
    glVertex2f(-1.65f, 0.57f);
    glEnd();
    glColor3ub(255, 51, 0);
    c = "open";
    glRasterPos2f(-1.715, 0.58);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c[i]);

    // Emergency priority - Horizontal GREEN, Vertical RED
    if (ambulanceOn || firetruckOn) {
        emergencyActive = 1;
        redgreen_emergency();
    }
    else {
        emergencyActive = 0;
        if (extraCarsOnRoad1 == 1) {
            cnt = 1;
            redgreen1();
        }
        else if (extraCarsOnRoad2 == 1) {
            cnt = 0;
            redgreen2();
        }
        else {
            if (cnt == 0) redgreen2();
            else redgreen1();
        }
    }

    if (r != 0) rain();
    glFlush();
}

void night() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3ub(15, 61, 15);
    glVertex2f(2.0f, 1.0f);
    glVertex2f(2.0f, -1.0f);
    glVertex2f(-2.0f, -1.0f);
    glVertex2f(-2.0f, 1.0f);
    glEnd();

    river();
    glBegin(GL_POLYGON);
    glColor3ub(15, 61, 15);
    glVertex2f(0.35f, -0.5f);
    glVertex2f(1.9f, -0.5f);
    glVertex2f(1.9f, -1.0f);
    glVertex2f(0.35f, -1.0f);
    glEnd();

    // Night trees (darker) – unchanged
    glLineWidth(10.0f);
    glBegin(GL_LINES);
    glColor3ub(153, 51, 51);
    glVertex2f(-1.5f, 0.8f);
    glVertex2f(-1.5f, 0.55f);
    glEnd();
    x = -1.45f; y = 0.82f; radius = 0.08f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(0, 102, 34);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = -1.5f; y = 0.85f; radius = 0.08f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(0, 102, 34);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = -1.55f; y = 0.82f; radius = 0.08f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(0, 102, 34);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-1.53f, 0.85f);
    glVertex2f(-1.47f, 0.8f);
    glEnd();

    glLineWidth(10.0f);
    glBegin(GL_LINES);
    glColor3ub(153, 51, 51);
    glVertex2f(-0.8f, 0.8f);
    glVertex2f(-0.8f, 0.57f);
    glEnd();
    x = -0.85f; y = 0.82f; radius = 0.08f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(0, 102, 34);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = -0.8f; y = 0.85f; radius = 0.08f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(0, 102, 34);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    x = -0.75f; y = 0.82f; radius = 0.08f;
    triangleAmount = 50;
    twicePi = 2.0f * PI;
    glColor3ub(0, 102, 34);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(153, 51, 51);
    glVertex2f(1.55f, 0.65f);
    glVertex2f(1.55f, 0.8f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 102, 34);
    glVertex2f(1.45f, 0.7f);
    glVertex2f(1.55f, 0.95f);
    glVertex2f(1.65f, 0.7f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(153, 51, 51);
    glVertex2f(-0.2f, 0.65f);
    glVertex2f(-0.2f, 0.8f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 102, 34);
    glVertex2f(-0.3f, 0.7f);
    glVertex2f(-0.2f, 0.95f);
    glVertex2f(-0.1f, 0.7f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(153, 51, 51);
    glVertex2f(1.9f, 0.7f);
    glVertex2f(1.9f, 0.85f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 102, 34);
    glVertex2f(1.8f, 0.75f);
    glVertex2f(1.9f, 1.0f);
    glVertex2f(2.0f, 0.75f);
    glEnd();

    // Night road
    glBegin(GL_POLYGON);
    glColor3ub(40, 40, 40);
    glVertex2f(-2.0f, 0.7f);
    glVertex2f(2.0f, 0.7f);
    glVertex2f(2.0f, -0.7f);
    glVertex2f(-2.0f, -0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(40, 40, 40);
    glVertex2f(0.3f, 1.0f);
    glVertex2f(1.5f, 1.0f);
    glVertex2f(1.5f, -1.0f);
    glVertex2f(0.3f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(-2.0f, 0.7f);
    glVertex2f(-2.0f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, 0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(-2.0f, -0.7f);
    glVertex2f(-2.0f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, -0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(2.0f, -0.7f);
    glVertex2f(2.0f, -0.5f);
    glVertex2f(1.3f, -0.5f);
    glVertex2f(1.3f, -0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(2.0f, 0.7f);
    glVertex2f(2.0f, 0.5f);
    glVertex2f(1.3f, 0.5f);
    glVertex2f(1.3f, 0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(0.3f, -1.0f);
    glVertex2f(0.5f, -1.0f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.3f, -0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(1.3f, -1.0f);
    glVertex2f(1.5f, -1.0f);
    glVertex2f(1.5f, -0.5f);
    glVertex2f(1.3f, -0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(1.3f, 1.0f);
    glVertex2f(1.5f, 1.0f);
    glVertex2f(1.5f, 0.5f);
    glVertex2f(1.3f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(0.3f, 1.0f);
    glVertex2f(0.5f, 1.0f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.3f, 0.5f);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(-2.0f, 0.0f);
    glVertex2f(-1.8f, 0.0f);
    glVertex2f(-1.7f, 0.0f);
    glVertex2f(-1.5f, 0.0f);
    glVertex2f(-1.4f, 0.0f);
    glVertex2f(-1.2f, 0.0f);
    glVertex2f(-1.1f, 0.0f);
    glVertex2f(-0.9f, 0.0f);
    glVertex2f(-0.8f, 0.0f);
    glVertex2f(-0.6f, 0.0f);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(-0.3f, 0.0f);
    glVertex2f(-0.2f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.9f, 0.8f);
    glVertex2f(0.9f, 0.97f);
    glVertex2f(0.9f, -0.97f);
    glVertex2f(0.9f, -0.8f);
    glVertex2f(1.7f, 0.0f);
    glVertex2f(1.9f, 0.0f);
    glEnd();

    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.2f, 0.5f);
    glVertex2f(0.2f, -0.5f);
    glVertex2f(0.4f, -0.5f);
    glVertex2f(0.4f, 0.5f);
    glVertex2f(1.5f, 0.5f);
    glVertex2f(1.5f, -0.5f);
    glVertex2f(1.7f, 0.5f);
    glVertex2f(1.7f, -0.5f);
    glVertex2f(0.5f, 0.7f);
    glVertex2f(1.3f, 0.7f);
    glVertex2f(0.5f, 0.9f);
    glVertex2f(1.3f, 0.9f);
    glVertex2f(0.5f, -0.7f);
    glVertex2f(1.3f, -0.7f);
    glVertex2f(0.5f, -0.9f);
    glVertex2f(1.3f, -0.9f);
    glEnd();

    glLineWidth(10.0f);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.4f, 0.2f);
    glVertex2f(0.2f, 0.1f);
    glVertex2f(0.4f, 0.1f);
    glVertex2f(0.2f, 0.0f);
    glVertex2f(0.4f, 0.0f);
    glVertex2f(0.2f, -0.1f);
    glVertex2f(0.4f, -0.1f);
    glVertex2f(0.2f, -0.2f);
    glVertex2f(0.4f, -0.2f);
    glVertex2f(1.5f, 0.2f);
    glVertex2f(1.7f, 0.2f);
    glVertex2f(1.5f, 0.1f);
    glVertex2f(1.7f, 0.1f);
    glVertex2f(1.5f, 0.0f);
    glVertex2f(1.7f, 0.0f);
    glVertex2f(1.5f, -0.1f);
    glVertex2f(1.7f, -0.1f);
    glVertex2f(1.5f, -0.2f);
    glVertex2f(1.7f, -0.2f);
    glVertex2f(0.7f, -0.5f);
    glVertex2f(0.7f, -0.7f);
    glVertex2f(0.8f, -0.5f);
    glVertex2f(0.8f, -0.7f);
    glVertex2f(0.9f, -0.5f);
    glVertex2f(0.9f, -0.7f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(1.0f, -0.7f);
    glVertex2f(1.1f, -0.5f);
    glVertex2f(1.1f, -0.7f);
    glVertex2f(0.7f, 0.5f);
    glVertex2f(0.7f, 0.7f);
    glVertex2f(0.8f, 0.5f);
    glVertex2f(0.8f, 0.7f);
    glVertex2f(0.9f, 0.5f);
    glVertex2f(0.9f, 0.7f);
    glVertex2f(1.0f, 0.5f);
    glVertex2f(1.0f, 0.7f);
    glVertex2f(1.1f, 0.5f);
    glVertex2f(1.1f, 0.7f);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(55, 55, 55);
    glVertex2f(-2.0f, 0.7f);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.3f, 1.0f);
    glVertex2f(1.5f, 1.0f);
    glVertex2f(1.5f, 0.7f);
    glVertex2f(1.5f, 0.7f);
    glVertex2f(2.0f, 0.7f);
    glVertex2f(2.0f, -0.7f);
    glVertex2f(1.5f, -0.7f);
    glVertex2f(1.5f, -0.7f);
    glVertex2f(1.5f, -1.0f);
    glVertex2f(0.3f, -1.0f);
    glVertex2f(0.3f, -0.7f);
    glVertex2f(0.3f, -0.7f);
    glVertex2f(-2.0f, -0.7f);
    glColor3ub(150, 150, 150);
    glVertex2f(-2.0f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, 1.0f);
    glVertex2f(1.3f, 1.0f);
    glVertex2f(1.3f, 0.5f);
    glVertex2f(1.3f, 0.5f);
    glVertex2f(2.0f, 0.5f);
    glVertex2f(2.0f, -0.5f);
    glVertex2f(1.3f, -0.5f);
    glVertex2f(1.3f, -0.5f);
    glVertex2f(1.3f, -1.0f);
    glVertex2f(0.5f, -1.0f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(-2.0f, -0.5f);
    glEnd();

    car1();
    car2();
    car3();
    car4();

    if (extraCarsOnRoad1 == 1) {
        car1_extra();
        car2_extra();
    }
    if (extraCarsOnRoad2 == 1) {
        car3_extra();
        car4_extra();
    }

    // Show only the active vehicle when alternating
    if (!alternatingMode || currentVehicle == 0) ambulance();
    if (!alternatingMode || currentVehicle == 1) firetruck();

    traffic_light1();
    traffic_light2();

    // Night road lights (unchanged)
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(-1.9f, 0.45f);
    glVertex2f(-1.8f, 0.45f);
    glVertex2f(-1.8f, 0.45f);
    glVertex2f(-1.8f, 0.15f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);
    glVertex2f(-1.85f, 0.28f);
    glVertex2f(-1.8f, 0.28f);
    glVertex2f(-1.8f, 0.15f);
    glVertex2f(-1.85f, 0.15f);
    glEnd();
    glPointSize(8.0);
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(-1.9f, 0.45f);
    glEnd();

    for (int i = 0; i < 3; i++) {
        glTranslated(0.6, 0.0, 0.0);
        glBegin(GL_LINES);
        glColor3ub(128, 128, 128);
        glVertex2f(-1.9f, 0.45f);
        glVertex2f(-1.8f, 0.45f);
        glVertex2f(-1.8f, 0.45f);
        glVertex2f(-1.8f, 0.15f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 0);
        glVertex2f(-1.85f, 0.28f);
        glVertex2f(-1.8f, 0.28f);
        glVertex2f(-1.8f, 0.15f);
        glVertex2f(-1.85f, 0.15f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3ub(89, 89, 89);
        glVertex2f(-1.9f, 0.45f);
        glEnd();
    }

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(-1.6f, -0.45f);
    glVertex2f(-1.5f, -0.45f);
    glVertex2f(-1.5f, -0.45f);
    glVertex2f(-1.5f, -0.15f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);
    glVertex2f(-1.5f, -0.15f);
    glVertex2f(-1.55f, -0.15f);
    glVertex2f(-1.55f, -0.28f);
    glVertex2f(-1.5f, -0.28f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(-1.6f, -0.45f);
    glEnd();

    for (int i = 0; i < 3; i++) {
        glTranslated(-0.6, 0.0, 0.0);
        glBegin(GL_LINES);
        glColor3ub(128, 128, 128);
        glVertex2f(-1.6f, -0.45f);
        glVertex2f(-1.5f, -0.45f);
        glVertex2f(-1.5f, -0.45f);
        glVertex2f(-1.5f, -0.15f);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 0);
        glVertex2f(-1.5f, -0.15f);
        glVertex2f(-1.55f, -0.15f);
        glVertex2f(-1.55f, -0.28f);
        glVertex2f(-1.5f, -0.28f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3ub(89, 89, 89);
        glVertex2f(-1.6f, -0.45f);
        glEnd();
    }

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(1.4f, 0.45f);
    glVertex2f(1.5f, 0.45f);
    glVertex2f(1.5f, 0.45f);
    glVertex2f(1.5f, 0.15f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);
    glVertex2f(1.5f, 0.15f);
    glVertex2f(1.45f, 0.15f);
    glVertex2f(1.45f, 0.28f);
    glVertex2f(1.5f, 0.28f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(1.4f, 0.45f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(1.7f, -0.45f);
    glVertex2f(1.8f, -0.45f);
    glVertex2f(1.8f, -0.45f);
    glVertex2f(1.8f, -0.15f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);
    glVertex2f(1.8f, -0.15f);
    glVertex2f(1.75f, -0.15f);
    glVertex2f(1.75f, -0.28f);
    glVertex2f(1.8f, -0.28f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(1.7f, -0.45f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(0.55f, -0.7f);
    glVertex2f(0.55f, -0.6f);
    glVertex2f(0.55f, -0.6f);
    glVertex2f(0.75f, -0.6f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);
    glVertex2f(0.75f, -0.6f);
    glVertex2f(0.75f, -0.65f);
    glVertex2f(0.62f, -0.65f);
    glVertex2f(0.62f, -0.6f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(0.55f, -0.7f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(1.25f, -0.7f);
    glVertex2f(1.25f, -0.6f);
    glVertex2f(1.25f, -0.6f);
    glVertex2f(1.05f, -0.6f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);
    glVertex2f(1.05f, -0.6f);
    glVertex2f(1.05f, -0.65f);
    glVertex2f(1.18f, -0.65f);
    glVertex2f(1.18f, -0.6f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(1.25f, -0.7f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(0.55f, 0.7f);
    glVertex2f(0.55f, 0.8f);
    glVertex2f(0.55f, 0.8f);
    glVertex2f(0.75f, 0.8f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);
    glVertex2f(0.75f, 0.8f);
    glVertex2f(0.75f, 0.75f);
    glVertex2f(0.62f, 0.75f);
    glVertex2f(0.62f, 0.8f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(0.55f, 0.7f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(1.25f, 0.7f);
    glVertex2f(1.25f, 0.8f);
    glVertex2f(1.25f, 0.8f);
    glVertex2f(1.05f, 0.8f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);
    glVertex2f(1.05f, 0.8f);
    glVertex2f(1.05f, 0.75f);
    glVertex2f(1.18f, 0.75f);
    glVertex2f(1.18f, 0.8f);
    glEnd();
    glBegin(GL_POINTS);
    glColor3ub(89, 89, 89);
    glVertex2f(1.25f, 0.7f);
    glEnd();

    factory();
    glPushMatrix();
    windmill();
    glPopMatrix();
    fence();

    // Night shops (unchanged) – omitted for brevity, but in your full code they are present.

    // ... (the rest of night() is the same as your original, including the shops, houses, etc.)

    // Night shops
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-1.95f, 0.5f);
    glVertex2f(-1.95f, 0.75f);
    glVertex2f(-1.55f, 0.75f);
    glVertex2f(-1.55f, 0.5f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(128, 0, 0);
    glVertex2f(-1.95f, 0.75f);
    glVertex2f(-1.95f, 0.85f);
    glVertex2f(-1.55f, 0.85f);
    glVertex2f(-1.55f, 0.75f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex2f(-2.0f, 0.65f);
    glVertex2f(-1.5f, 0.65f);
    glVertex2f(-1.5f, 0.7f);
    glVertex2f(-1.55f, 0.75f);
    glVertex2f(-1.95f, 0.75f);
    glVertex2f(-2.0f, 0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 153, 51);
    glVertex2f(-1.9f, 0.5f);
    glVertex2f(-1.9f, 0.62f);
    glColor3ub(179, 119, 0);
    glVertex2f(-1.82f, 0.62f);
    glVertex2f(-1.82f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 153, 51);
    glVertex2f(-1.77f, 0.55f);
    glVertex2f(-1.77f, 0.62f);
    glColor3ub(179, 119, 0);
    glVertex2f(-1.6f, 0.62f);
    glVertex2f(-1.6f, 0.55f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 0, 0);
    glVertex2f(-1.52f, 0.5f);
    glVertex2f(-1.98f, 0.5f);
    glVertex2f(-1.524f, 0.504f);
    glVertex2f(-1.98f, 0.504f);
    glVertex2f(-1.9f, 0.5f);
    glVertex2f(-1.9f, 0.62f);
    glVertex2f(-1.9f, 0.62f);
    glVertex2f(-1.82f, 0.62f);
    glVertex2f(-1.82f, 0.62f);
    glVertex2f(-1.82f, 0.5f);
    glVertex2f(-1.82f, 0.5f);
    glVertex2f(-1.9f, 0.5f);
    glVertex2f(-1.82f, 0.55f);
    glVertex2f(-1.9f, 0.55f);
    glVertex2f(-1.77f, 0.55f);
    glVertex2f(-1.77f, 0.62f);
    glVertex2f(-1.77f, 0.62f);
    glVertex2f(-1.6f, 0.62f);
    glVertex2f(-1.6f, 0.62f);
    glVertex2f(-1.6f, 0.55f);
    glVertex2f(-1.6f, 0.55f);
    glVertex2f(-1.77f, 0.55f);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    c = "BFC";
    glRasterPos2f(-1.8, 0.78);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);

    glBegin(GL_POLYGON);
    glColor3ub(255, 204, 102);
    glVertex2f(-0.75f, 0.5f);
    glVertex2f(-0.75f, 0.8f);
    glVertex2f(-0.2f, 0.8f);
    glVertex2f(-0.2f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(179, 89, 0);
    glVertex2f(-0.75f, 0.85f);
    glVertex2f(-0.75f, 0.8f);
    glVertex2f(-0.2f, 0.8f);
    glVertex2f(-0.2f, 0.85f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(179, 89, 0);
    glVertex2f(-0.3f, 0.85f);
    glVertex2f(-0.35f, 0.9f);
    glVertex2f(-0.6f, 0.9f);
    glVertex2f(-0.66f, 0.85f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(102, 82, 0);
    glVertex2f(-0.73f, 0.5f);
    glVertex2f(-0.73f, 0.8);
    glVertex2f(-0.22f, 0.8);
    glVertex2f(-0.22f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(230, 115, 0);
    glVertex2f(-0.8f, 0.7f);
    glVertex2f(-0.15f, 0.7f);
    glVertex2f(-0.15f, 0.75f);
    glVertex2f(-0.2f, 0.8f);
    glVertex2f(-0.75f, 0.8f);
    glVertex2f(-0.8f, 0.75f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 0, 0);
    glVertex2f(-0.17f, 0.5f);
    glVertex2f(-0.77f, 0.5f);
    glVertex2f(-0.17f, 0.504f);
    glVertex2f(-0.77f, 0.504f);
    glColor3ub(255, 153, 51);
    glVertex2f(-0.73f, 0.53f);
    glVertex2f(-0.22f, 0.53f);
    glVertex2f(-0.73f, 0.56f);
    glVertex2f(-0.22f, 0.56f);
    glVertex2f(-0.73f, 0.59f);
    glVertex2f(-0.22f, 0.59f);
    glVertex2f(-0.73f, 0.62f);
    glVertex2f(-0.22f, 0.62f);
    glVertex2f(-0.73f, 0.65f);
    glVertex2f(-0.22f, 0.65f);
    glVertex2f(-0.73f, 0.68f);
    glVertex2f(-0.22f, 0.68f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 235, 153);
    glVertex2f(-0.4f, 0.58f);
    glVertex2f(-0.4f, 0.65f);
    glVertex2f(-0.25f, 0.65f);
    glVertex2f(-0.25f, 0.58f);
    glEnd();

    glColor3ub(102, 51, 0);
    c = "closed";
    glRasterPos2f(-0.39, 0.6);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c[i]);

    glColor3ub(255, 255, 0);
    c = "Candy Shop";
    glRasterPos2f(-0.6, 0.84);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[i]);

    // Night houses (simplified)
    glBegin(GL_POLYGON);
    glColor3ub(224, 228, 231);
    glVertex2f(-1.4f, 0.5f);
    glVertex2f(-1.4f, 1.0f);
    glVertex2f(-0.9f, 1.0f);
    glVertex2f(-0.9f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(204, 255, 153);
    glVertex2f(-1.35f, 0.55f);
    glVertex2f(-1.35f, 0.65f);
    glColor3ub(128, 255, 0);
    glVertex2f(-1.25f, 0.65f);
    glVertex2f(-1.25f, 0.55f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(204, 255, 153);
    glVertex2f(-1.05f, 0.55f);
    glVertex2f(-1.05f, 0.65f);
    glColor3ub(128, 255, 0);
    glVertex2f(-0.95f, 0.65f);
    glVertex2f(-0.95f, 0.55f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(204, 255, 153);
    glVertex2f(-1.35f, 0.85f);
    glVertex2f(-1.35f, 0.95f);
    glColor3ub(128, 255, 0);
    glVertex2f(-1.25f, 0.95f);
    glVertex2f(-1.25f, 0.85f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(204, 255, 153);
    glVertex2f(-1.2f, 0.85f);
    glVertex2f(-1.2f, 0.95f);
    glColor3ub(128, 255, 0);
    glVertex2f(-1.1f, 0.95f);
    glVertex2f(-1.1f, 0.85f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(204, 255, 153);
    glVertex2f(-1.05f, 0.85f);
    glVertex2f(-1.05f, 0.95f);
    glColor3ub(128, 255, 0);
    glVertex2f(-0.95f, 0.95f);
    glVertex2f(-0.95f, 0.85f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(-1.2f, 0.5f);
    glVertex2f(-1.2f, 0.65f);
    glVertex2f(-1.1f, 0.65f);
    glVertex2f(-1.1f, 0.5f);
    glEnd();

    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-1.17f, 0.58f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(77, 195, 255);
    glVertex2f(-1.35f, 0.55f);
    glVertex2f(-1.35f, 0.65f);
    glVertex2f(-1.35f, 0.65f);
    glVertex2f(-1.25f, 0.65f);
    glVertex2f(-1.25f, 0.65f);
    glVertex2f(-1.25f, 0.55f);
    glVertex2f(-1.25f, 0.55f);
    glVertex2f(-1.35f, 0.55f);
    glVertex2f(-1.25f, 0.6f);
    glVertex2f(-1.35f, 0.6f);
    glVertex2f(-1.05f, 0.55f);
    glVertex2f(-1.05f, 0.65f);
    glVertex2f(-1.05f, 0.65f);
    glVertex2f(-0.95f, 0.65f);
    glVertex2f(-0.95f, 0.65f);
    glVertex2f(-0.95f, 0.55f);
    glVertex2f(-0.95f, 0.55f);
    glVertex2f(-1.05f, 0.55f);
    glVertex2f(-0.95f, 0.6f);
    glVertex2f(-1.05f, 0.6f);
    glVertex2f(-1.35f, 0.85f);
    glVertex2f(-1.35f, 0.95f);
    glVertex2f(-1.35f, 0.95f);
    glVertex2f(-1.25f, 0.95f);
    glVertex2f(-1.25f, 0.95f);
    glVertex2f(-1.25f, 0.85f);
    glVertex2f(-1.25f, 0.85f);
    glVertex2f(-1.35f, 0.85f);
    glVertex2f(-1.25f, 0.9f);
    glVertex2f(-1.35f, 0.9f);
    glVertex2f(-1.2f, 0.85f);
    glVertex2f(-1.2f, 0.95f);
    glVertex2f(-1.2f, 0.95f);
    glVertex2f(-1.1f, 0.95f);
    glVertex2f(-1.1f, 0.95f);
    glVertex2f(-1.1f, 0.85f);
    glVertex2f(-1.1f, 0.85f);
    glVertex2f(-1.2f, 0.85f);
    glVertex2f(-1.1f, 0.9f);
    glVertex2f(-1.2f, 0.9f);
    glVertex2f(-1.05f, 0.85f);
    glVertex2f(-1.05f, 0.95f);
    glVertex2f(-1.05f, 0.95f);
    glVertex2f(-0.95f, 0.95f);
    glVertex2f(-0.95f, 0.95f);
    glVertex2f(-0.95f, 0.85f);
    glVertex2f(-0.95f, 0.85f);
    glVertex2f(-1.05f, 0.85f);
    glVertex2f(-0.95f, 0.9f);
    glVertex2f(-1.05f, 0.9f);
    glVertex2f(-1.2f, 0.5f);
    glVertex2f(-1.2f, 0.65f);
    glVertex2f(-1.2f, 0.65f);
    glVertex2f(-1.1f, 0.65f);
    glVertex2f(-1.1f, 0.65f);
    glVertex2f(-1.1f, 0.5f);
    glVertex2f(-1.1f, 0.5f);
    glVertex2f(-1.2f, 0.5f);
    glColor3ub(128, 128, 128);
    glVertex2f(-1.4f, 0.5f);
    glVertex2f(-1.4f, 1.0f);
    glVertex2f(-1.4f, 1.0f);
    glVertex2f(-0.9f, 1.0f);
    glVertex2f(-0.9f, 1.0f);
    glVertex2f(-0.9f, 0.5f);
    glColor3ub(128, 0, 0);
    glVertex2f(-0.87f, 0.5f);
    glVertex2f(-1.43f, 0.5f);
    glVertex2f(-0.87f, 0.504f);
    glVertex2f(-1.43f, 0.504f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(76, 174, 218);
    glVertex2f(-1.4f, 0.8f);
    glVertex2f(-1.45f, 0.75f);
    glVertex2f(-1.45f, 0.7f);
    glVertex2f(-0.85f, 0.7f);
    glVertex2f(-0.85f, 0.75f);
    glVertex2f(-0.9f, 0.8f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(128, 128, 128);
    glVertex2f(-1.4f, 0.8f);
    glVertex2f(-1.45f, 0.75f);
    glVertex2f(-1.45f, 0.75f);
    glVertex2f(-1.45f, 0.7f);
    glVertex2f(-1.45f, 0.7f);
    glVertex2f(-0.85f, 0.7f);
    glVertex2f(-0.85f, 0.7f);
    glVertex2f(-0.85f, 0.75f);
    glVertex2f(-0.85f, 0.75f);
    glVertex2f(-0.9f, 0.8f);
    glVertex2f(-0.9f, 0.8f);
    glVertex2f(-1.4f, 0.8f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(153, 51, 0);
    glVertex2f(-0.15f, 0.5f);
    glVertex2f(-0.15f, 0.8f);
    glVertex2f(0.35f, 0.8f);
    glVertex2f(0.35f, 0.5f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(153, 51, 0);
    glVertex2f(0.05f, 0.8f);
    glVertex2f(0.05f, 0.99f);
    glVertex2f(0.35f, 0.99f);
    glVertex2f(0.35f, 0.8f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(102, 153, 0);
    glVertex2f(0.05f, 0.6f);
    glVertex2f(0.05f, 0.7f);
    glColor3ub(85, 128, 0);
    glVertex2f(0.15f, 0.7f);
    glVertex2f(0.15f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(102, 153, 0);
    glVertex2f(0.2f, 0.6f);
    glVertex2f(0.2f, 0.7f);
    glColor3ub(85, 128, 0);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.3f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(102, 153, 0);
    glVertex2f(0.15f, 0.85f);
    glVertex2f(0.15f, 0.95f);
    glColor3ub(85, 128, 0);
    glVertex2f(0.25f, 0.95f);
    glVertex2f(0.25f, 0.85f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(40, 40, 40);
    glVertex2f(-0.1f, 0.5f);
    glVertex2f(-0.1f, 0.65f);
    glVertex2f(0.0f, 0.65f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.03f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(230, 115, 0);
    glVertex2f(0.02f, 0.65f);
    glVertex2f(-0.05f, 0.7f);
    glVertex2f(-0.12f, 0.65f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(0.15f, 0.85f);
    glVertex2f(0.15f, 0.95f);
    glVertex2f(0.15f, 0.95f);
    glVertex2f(0.25f, 0.95f);
    glVertex2f(0.25f, 0.95f);
    glVertex2f(0.25f, 0.85f);
    glVertex2f(0.25f, 0.85f);
    glVertex2f(0.15f, 0.85f);
    glVertex2f(0.05f, 0.6f);
    glVertex2f(0.05f, 0.7f);
    glVertex2f(0.05f, 0.7f);
    glVertex2f(0.15f, 0.7f);
    glVertex2f(0.15f, 0.7f);
    glVertex2f(0.15f, 0.6f);
    glVertex2f(0.15f, 0.6f);
    glVertex2f(0.05f, 0.6f);
    glVertex2f(0.2f, 0.6f);
    glVertex2f(0.2f, 0.7f);
    glVertex2f(0.2f, 0.7f);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.3f, 0.6f);
    glVertex2f(0.3f, 0.6f);
    glVertex2f(0.2f, 0.6f);
    glColor3ub(255, 153, 51);
    glVertex2f(-0.1f, 0.5f);
    glVertex2f(-0.1f, 0.65f);
    glVertex2f(-0.1f, 0.65f);
    glVertex2f(0.0f, 0.65f);
    glVertex2f(0.0f, 0.65f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.1f, 0.5f);
    glVertex2f(0.02f, 0.65f);
    glVertex2f(-0.05f, 0.7f);
    glVertex2f(-0.05f, 0.7f);
    glVertex2f(-0.12f, 0.65f);
    glVertex2f(-0.12f, 0.65f);
    glVertex2f(0.02f, 0.65f);
    glVertex2f(0.36f, 0.8f);
    glVertex2f(-0.16f, 0.8f);
    glVertex2f(0.36f, 0.84f);
    glVertex2f(-0.16f, 0.84f);
    glVertex2f(-0.14f, 0.8f);
    glVertex2f(-0.14f, 0.84f);
    glVertex2f(-0.1f, 0.8f);
    glVertex2f(-0.1f, 0.84f);
    glVertex2f(-0.05f, 0.8f);
    glVertex2f(-0.05f, 0.84f);
    glVertex2f(-0.0f, 0.8f);
    glVertex2f(-0.0f, 0.84f);
    glVertex2f(0.05f, 0.8f);
    glVertex2f(0.05f, 0.84f);
    glVertex2f(0.1f, 0.8f);
    glVertex2f(0.1f, 0.84f);
    glVertex2f(0.15f, 0.8f);
    glVertex2f(0.15f, 0.84f);
    glVertex2f(0.2f, 0.8f);
    glVertex2f(0.2f, 0.84f);
    glVertex2f(0.25f, 0.8f);
    glVertex2f(0.25f, 0.84f);
    glVertex2f(0.3f, 0.8f);
    glVertex2f(0.3f, 0.84f);
    glVertex2f(0.35f, 0.8f);
    glVertex2f(0.35f, 0.84f);
    glVertex2f(-0.16f, 0.504f);
    glVertex2f(0.36f, 0.504f);
    glVertex2f(-0.16f, 0.5f);
    glVertex2f(0.36f, 0.5f);
    glVertex2f(0.04f, 0.99f);
    glVertex2f(0.36f, 0.99f);
    glVertex2f(0.04f, 0.985f);
    glVertex2f(0.36f, 0.985f);
    glEnd();

    boat1_shore();
    boat2_shore();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 204);
    glVertex2f(-1.72f, 0.57f);
    glVertex2f(-1.72f, 0.6f);
    glVertex2f(-1.65f, 0.6f);
    glVertex2f(-1.65f, 0.57f);
    glEnd();
    glColor3ub(255, 51, 0);
    c = "close";
    glRasterPos2f(-1.715, 0.58);
    for (int i = 0; c[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c[i]);

    // Emergency priority - Horizontal GREEN, Vertical RED
    if (ambulanceOn || firetruckOn) {
        emergencyActive = 1;
        redgreen_emergency();
    }
    else {
        emergencyActive = 0;
        if (extraCarsOnRoad1 == 1) {
            cnt = 1;
            redgreen1();
        }
        else if (extraCarsOnRoad2 == 1) {
            cnt = 0;
            redgreen2();
        }
        else {
            if (cnt == 0) redgreen2();
            else redgreen1();
        }
    }

    if (r != 0) rain();
    glFlush();
}

// ==================== UPDATE FUNCTIONS ====================

void update_car1(int value) {
    bool giveWay = false;
    bool ambulanceFullyPassed = false;

    if (emergencyActive) {
        giveWay = true;
        ambulancePassed = 1;
    }
    if (ambulanceOn && position_amb < position_c1 && (position_c1 - position_amb) < 0.55f) {
        giveWay = true;
        ambulancePassed = 1;
    }
    if (ambulanceOn && position_amb > position_c1 && (position_amb - position_c1) > 0.6f) {
        ambulanceFullyPassed = true;
        ambulancePassed = 2;
    }
    if (!ambulanceOn && !firetruckOn) emergencyActive = 0;

    if (giveWay) {
        if (car1_shift < 0.25f) car1_shift += 0.02f;
        speed_c1 = 0.0f;
    }
    else if (ambulanceFullyPassed || ambulancePassed == 2) {
        if (car1_shift > 0.0f) car1_shift -= 0.02f;
        if (cnt == 0) {
            speed_c1 = 0.01f;
            if (position_c1 > 2.7f) position_c1 = -2.7f;
            position_c1 += speed_c1;
            if (extraCarsOnRoad1 == 1) {
                if (position_c1_extra > 2.7f) position_c1_extra = -2.7f;
                position_c1_extra += speed_c1;
            }
        }
        else {
            if (position_c1 > 0.0f) { speed_c1 = 0.0f; position_c1 = 0.0f; }
            else {
                speed_c1 = 0.01f;
                position_c1 += speed_c1;
                if (extraCarsOnRoad1 == 1) {
                    if (position_c1_extra > 0.0f) position_c1_extra = 0.0f;
                    else position_c1_extra += speed_c1;
                }
            }
        }
    }
    else if (ambulancePassed == 1) {
        speed_c1 = 0.0f;
        if (car1_shift < 0.25f) car1_shift += 0.02f;
    }
    else {
        if (car1_shift > 0.0f) car1_shift -= 0.02f;
        if (cnt == 0) {
            speed_c1 = 0.01f;
            if (position_c1 > 2.7f) position_c1 = -2.7f;
            position_c1 += speed_c1;
            if (extraCarsOnRoad1 == 1) {
                if (position_c1_extra > 2.7f) position_c1_extra = -2.7f;
                position_c1_extra += speed_c1;
            }
        }
        else {
            if (position_c1 > 0.0f) { speed_c1 = 0.0f; position_c1 = 0.0f; }
            else {
                speed_c1 = 0.01f;
                position_c1 += speed_c1;
                if (extraCarsOnRoad1 == 1) {
                    if (position_c1_extra > 0.0f) position_c1_extra = 0.0f;
                    else position_c1_extra += speed_c1;
                }
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(10, update_car1, 0);
}

void update_car2(int value) {
    bool giveWay = false;

    if (firetruckOn) {
        giveWay = true;
    }

    if (giveWay) {
        speed_c2 = 0.0f;
    }
    else {
        if (cnt == 0) {
            speed_c2 = 0.01f;
            if (position_c2 < -2.7) position_c2 = 2.7f;
            position_c2 -= speed_c2;
            if (extraCarsOnRoad1 == 1) {
                if (position_c2_extra < -2.7) position_c2_extra = 2.7f;
                position_c2_extra -= speed_c2;
            }
        }
        else {
            if (position_c2 < 1.8) {
                speed_c2 = 0.0f;
                position_c2 = 1.8;
            }
            position_c2 -= speed_c2;
            if (extraCarsOnRoad1 == 1) {
                if (position_c2_extra < 1.8) {
                    position_c2_extra = 1.8;
                }
                position_c2_extra -= speed_c2;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(10, update_car2, 0);
}

void update_car3(int value) {
    bool giveWay = false;

    if (ambulanceOn && firetruckOn) {
        giveWay = true;
        if (car3_shift < 0.55f) car3_shift += 0.02f;
    }

    if (firetruckOn) {
        giveWay = true;
        if (car3_shift < 0.55f) car3_shift += 0.02f;
    }

    if (giveWay) {
        speed_c3 = 0.0f;
    }
    else {
        if (car3_shift > 0.0f) car3_shift -= 0.02f;
        if (cnt == 0) {
            if (position_c3 > -0.9) { speed_c3 = 0.0f; position_c3 = -0.9; }
            position_c3 += speed_c3;
            if (extraCarsOnRoad2 == 1) {
                if (position_c3_extra > -0.9) position_c3_extra = -0.9;
                position_c3_extra += speed_c3;
            }
        }
        else {
            speed_c3 = 0.01f;
            if (position_c3 > 1.7) position_c3 = -1.7f;
            position_c3 += speed_c3;
            if (extraCarsOnRoad2 == 1) {
                if (position_c3_extra > 1.7) position_c3_extra = -1.7f;
                position_c3_extra += speed_c3;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(10, update_car3, 0);
}

void update_car4(int value) {
    bool giveWay = false;

    if (ambulanceOn) {
        giveWay = true;
        if (car4_shift > 0.0f) car4_shift -= 0.02f;
    }

    if (firetruckOn) {
        giveWay = true;
        if (car4_shift > 0.0f) car4_shift -= 0.02f;
    }

    if (giveWay) {
        speed_c4 = 0.0f;
    }
    else {
        if (car4_shift > 0.0f) car4_shift -= 0.02f;
        if (cnt == 0) {
            if (position_c4 < 0.9) { speed_c4 = 0.0f; position_c4 = 0.9; }
            position_c4 -= speed_c4;
            if (extraCarsOnRoad2 == 1) {
                if (position_c4_extra < 0.9) position_c4_extra = 0.9;
                position_c4_extra -= speed_c4;
            }
        }
        else {
            speed_c4 = 0.01f;
            if (position_c4 < -1.7) position_c4 = 1.7f;
            position_c4 -= speed_c4;
            if (extraCarsOnRoad2 == 1) {
                if (position_c4_extra < -1.7) position_c4_extra = 1.7f;
                position_c4_extra -= speed_c4;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(10, update_car4, 0);
}

// ==================== UPDATED AMBULANCE WITH ALTERNATING LOGIC ====================
void update_ambulance(int value) {
    if (ambulanceOn) {
        emergencyActive = 1;

        // If alternating mode is active and it's not ambulance's turn, stay at start
        if (alternatingMode && currentVehicle != 0) {
            position_amb = -2.3f;  // keep at start (hidden)
            glutPostRedisplay();
            glutTimerFunc(10, update_ambulance, 0);
            return;
        }

        position_amb += speed_amb;
        if (position_amb > 2.3f) {
            // Ambulance finished its run
            position_amb = -2.3f;  // reset to start (hidden)
            if (alternatingMode) {
                // Switch to firetruck
                currentVehicle = 1;
                // Reset firetruck to start and ensure it moves
                position_fire = -1.3f;
                speed_fire = (ambulanceOn ? 0.015f : 0.025f);
            }
            else {
                // Not alternating, just loop normally
                position_amb = -2.3f;
            }
        }

        if (position_amb < position_c1 && (position_c1 - position_amb) < 0.55f) {
            if (car1_shift < 0.25f) car1_shift += 0.02f;
        }
    }
    else {
        if (!firetruckOn) emergencyActive = 0;
        position_amb = -2.3f;
        ambulancePassed = 0;
        if (car1_shift > 0.0f) car1_shift -= 0.008f;
        // If alternating mode was active, turn it off when ambulance is turned off
        if (alternatingMode && firetruckOn) {
            alternatingMode = 0;
            currentVehicle = 0;
        }
    }
    if (car1_shift < 0.0f) car1_shift = 0.0f;
    glutPostRedisplay();
    glutTimerFunc(10, update_ambulance, 0);
}

// ==================== UPDATED FIRETRUCK WITH ALTERNATING LOGIC ====================
void update_firetruck(int value) {
    if (firetruckOn) {
        emergencyActive = 1;

        // If alternating mode is active and it's not firetruck's turn, stay at start
        if (alternatingMode && currentVehicle != 1) {
            position_fire = -1.3f;  // keep at start (hidden)
            glutPostRedisplay();
            glutTimerFunc(10, update_firetruck, 0);
            return;
        }

        // Speed: if ambulance is also on but it's firetruck's turn, still slow
        if (ambulanceOn) {
            speed_fire = 0.015f;
        }
        else {
            speed_fire = 0.025f;
        }

        position_fire += speed_fire;
        if (position_fire > 1.3f) {
            // Firetruck finished its run
            position_fire = -1.3f;  // reset to start (hidden)
            if (alternatingMode) {
                // Switch back to ambulance
                currentVehicle = 0;
                // Reset ambulance to start
                position_amb = -2.3f;
                // Ensure ambulance moves
            }
            else {
                position_fire = -1.3f;
            }
        }

        // Shifting logic for cars (as before)
        if (position_fire < position_c3 && (position_c3 - position_fire) < 0.55f) {
            if (car3_shift < 0.2f) car3_shift += 0.02f;
        }
        else {
            if (car3_shift > 0.0f) car3_shift -= 0.008f;
        }

        if (position_fire < position_c4 && (position_c4 - position_fire) < 0.55f) {
            if (car4_shift < 0.2f) car4_shift += 0.02f;
        }
        else {
            if (car4_shift > 0.0f) car4_shift -= 0.008f;
        }
    }
    else {
        if (!ambulanceOn) emergencyActive = 0;
        position_fire = -1.3f;
        if (car3_shift > 0.0f) car3_shift -= 0.008f;
        if (car4_shift > 0.0f) car4_shift -= 0.008f;
        // If alternating mode was active, turn it off when firetruck is turned off
        if (alternatingMode && ambulanceOn) {
            alternatingMode = 0;
            currentVehicle = 0;
        }
    }

    if (car3_shift < 0.0f) car3_shift = 0.0f;
    if (car4_shift < 0.0f) car4_shift = 0.0f;

    glutPostRedisplay();
    glutTimerFunc(10, update_firetruck, 0);
}

// ==================== OTHER UPDATE FUNCTIONS (unchanged) ====================
void update_smoke(int value) {
    if (position_s > 2.1) position_s = 1.6f;
    position_s += speed_s;
    glutPostRedisplay();
    glutTimerFunc(100, update_smoke, 0);
}

void update_river(int value) {
    if (position_r < -0.5) position_r = 0.0f;
    position_r -= speed_r;
    glutPostRedisplay();
    glutTimerFunc(100, update_river, 0);
}

void update_boat1(int value) {
    if (position_b1 < -2.0f) position_b1 = 0.0f;
    position_b1 -= speed_b1;
    glutPostRedisplay();
    glutTimerFunc(100, update_boat1, 0);
}

void update_boat2(int value) {
    if (position_b2 > 0.0f) position_b2 = -2.0f;
    position_b2 += speed_b2;
    glutPostRedisplay();
    glutTimerFunc(100, update_boat2, 0);
}

void update_rain(int value) {
    if (position_rain < -0.1) position_rain = 0.3f;
    position_rain -= speed_rain;
    if (position_rain2 > 2.0) position_rain2 = 1.8f;
    position_rain2 += speed_rain2;
    glutPostRedisplay();
    glutTimerFunc(100, update_rain, 0);
}

void update_windmill(int v) {
    frameNumber++;
    glutPostRedisplay();
    glutTimerFunc(30, update_windmill, 0);
}

// ==================== INPUT HANDLERS ====================

void button(unsigned char key, int x, int y) {
    switch (key) {
    case 'f': glutDisplayFunc(day); break;
    case 'c':
        extraCarsOnRoad1 = 1; extraCarsOnRoad2 = 0;
        position_c1_extra = 0.2f; position_c2_extra = 1.8f;
        cnt = 1;
        cout << "CONGESTION on Road 1 - Road 2 signal = RED" << endl;
        glutPostRedisplay();
        break;
    case 'v':
        extraCarsOnRoad2 = 1; extraCarsOnRoad1 = 0;
        position_c3_extra = -1.7f; position_c4_extra = 0.1f;
        cnt = 0;
        cout << "CONGESTION on Road 2 - Road 1 signal = RED" << endl;
        glutPostRedisplay();
        break;
    case 'r':
        cnt = 1; extraCarsOnRoad1 = 0; extraCarsOnRoad2 = 0;
        cout << "Manual: Red Horizontal, Green Vertical" << endl;
        glutPostRedisplay();
        break;
    case 'g':
        cnt = 0; extraCarsOnRoad1 = 0; extraCarsOnRoad2 = 0;
        cout << "Manual: Green Horizontal, Red Vertical" << endl;
        glutPostRedisplay();
        break;
    case 'n':
        flag++; glutDisplayFunc(night); glutPostRedisplay();
        position_s = -5.0f; speed_s = 0.0f;
        break;
    case 'd':
        flag = 0; glutDisplayFunc(day); glutPostRedisplay();
        position_s = 1.6f; speed_s = 0.01f;
        break;
    case 'a':
    case 'A':
        ambulanceOn = !ambulanceOn;
        if (ambulanceOn) {
            position_amb = -2.3f; car1_shift = 0.0f; ambulancePassed = 0; emergencyActive = 1;
            // If both are on, start alternating mode with ambulance first
            if (firetruckOn) {
                alternatingMode = 1;
                currentVehicle = 0;   // ambulance first
                position_fire = -1.3f; // reset firetruck
            }
            cout << "AMBULANCE ACTIVATED" << endl;
        }
        else {
            ambulancePassed = 0;
            if (!firetruckOn) emergencyActive = 0;
            alternatingMode = 0;      // turn off alternating if ambulance is off
            currentVehicle = 0;
            cout << "Ambulance Deactivated" << endl;
        }
        glutPostRedisplay();
        break;
    case 't':
    case 'T':
        firetruckOn = !firetruckOn;
        if (firetruckOn) {
            position_fire = -1.3f; car3_shift = 0.0f; car4_shift = 0.0f; emergencyActive = 1;
            // If both are on, start alternating mode with ambulance first (since ambulance is already on)
            if (ambulanceOn) {
                alternatingMode = 1;
                currentVehicle = 0;   // ambulance first
                position_amb = -2.3f; // reset ambulance
            }
            cout << "FIRE TRUCK ACTIVATED" << endl;
        }
        else {
            if (!ambulanceOn) emergencyActive = 0;
            alternatingMode = 0;
            currentVehicle = 0;
            cout << "Fire Truck Deactivated" << endl;
        }
        glutPostRedisplay();
        break;
    }
}

void rain_button(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        r++;
        // PlaySound("rain.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    }
    if (button == GLUT_RIGHT_BUTTON) {
        r = 0;
        PlaySound(NULL, NULL, SND_ASYNC | SND_FILENAME);
    }
}

void inigl() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(-2, 2, -1, 1);
}

// ==================== MAIN ====================

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1430, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Smart City Adaptive Traffic Management System");

    cout << "============================================================" << endl;
    cout << "Smart City Adaptive Traffic Management System" << endl;
    cout << "============================================================" << endl;
    cout << "Group: Naima Tabachchum Meem (C231414)" << endl;
    cout << "       Maisha Maliha (C231427)" << endl;
    cout << "============================================================" << endl;
    cout << "FEATURE: Alternating emergency vehicles when both are ON" << endl;
    cout << "============================================================" << endl;
    cout << "EMERGENCY PRIORITY SYSTEM:" << endl;
    cout << "  - Ambulance goes first, then firetruck, then ambulance..." << endl;
    cout << "  - Each vehicle waits for the other to fully exit." << endl;
    cout << "============================================================" << endl;
    cout << "CONTROLS:" << endl;
    cout << "F - Start Simulation" << endl;
    cout << "R - Manual: Red Horizontal, Green Vertical" << endl;
    cout << "G - Manual: Green Horizontal, Red Vertical" << endl;
    cout << "C - CONGESTION on Road 1 -> Road 2 gets RED" << endl;
    cout << "V - CONGESTION on Road 2 -> Road 1 gets RED" << endl;
    cout << "A - Toggle Ambulance" << endl;
    cout << "T - Toggle Fire Truck" << endl;
    cout << "D - Day Mode | N - Night Mode" << endl;
    cout << "LMB - Start Rain | RMB - Stop Rain" << endl;
    cout << "============================================================" << endl;

    glutDisplayFunc(start);
    inigl();
    glutTimerFunc(30, update_windmill, 0);
    glutTimerFunc(100, update_boat1, 0);
    glutTimerFunc(100, update_boat2, 0);
    glutTimerFunc(100, update_river, 0);
    glutTimerFunc(100, update_smoke, 0);
    glutTimerFunc(10, update_car1, 0);
    glutTimerFunc(10, update_car2, 0);
    glutTimerFunc(10, update_car3, 0);
    glutTimerFunc(10, update_car4, 0);
    glutTimerFunc(10, update_ambulance, 0);
    glutTimerFunc(10, update_firetruck, 0);
    glutTimerFunc(100, update_rain, 0);

    glutKeyboardFunc(button);
    glutMouseFunc(rain_button);

    glutMainLoop();
    return 0;
}