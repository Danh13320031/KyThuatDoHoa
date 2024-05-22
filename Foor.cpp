#include <glut.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "model.h"
#include <cmath>
//#include "imageloader.h"
//#include "texturemodel.h"

namespace Foor {
	Vector3 trans;
	Model* model, model1;
	//GLuint textureID;
	int nPoints = 3;
	double angle = 0;
	bool rotate = false;

	float cameraX = 0.0f, cameraY = 2.0f, cameraZ = 15.0f;
	float cameraYaw = 0.0f;

	void processSpecialKeys(int key, int xx, int yy) {
		switch (key) {
		case GLUT_KEY_LEFT:
			cameraYaw -= 5.0f;
			break;
		case GLUT_KEY_RIGHT:
			cameraYaw += 5.0f;
			break;
		case GLUT_KEY_UP:
			cameraX += sinf(cameraYaw * PI / 180.0f);
			cameraZ -= cosf(cameraYaw * PI / 180.0f);
			break;
		case GLUT_KEY_DOWN:
			cameraX -= sinf(cameraYaw * PI / 180.0f);
			cameraZ += cosf(cameraYaw * PI / 180.0f);
			break;
		}
		glutPostRedisplay();
	}

	//void loadTexture(const char* filename) {
		// Load hình ảnh texture bằng imageloader.h
		//Image* image = loadBMP(filename);

		// Tạo và thiết lập texture bằng texturemodel.h
		//glGenTextures(1, &textureID);
		//glBindTexture(GL_TEXTURE_2D, textureID);
		//setTextureFromBMP(image);

		// Xóa bộ nhớ được cấp phát cho image
		//delete image;
	//}

	void settingWall() {
		//glBindTexture(GL_TEXTURE_2D, textureID);

		glBegin(GL_QUADS);
			glColor3f(0.3, 0.3, 0.3); // Màu đỏ
			//glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-0.5, -0.5, 0.0);
			//glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.5, -0.5, 0.0);
			//glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.5, 0.5, 0.0);
			//glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-0.5, 0.5, 0.0);
			//glVertex3f(-0.5, -0.5, 0.0); // Đỉnh trái dưới
			//glVertex3f(0.5, -0.5, 0.0);  // Đỉnh phải dưới
			//glVertex3f(0.5, 0.5, 0.0);   // Đỉnh phải trên
			//glVertex3f(-0.5, 0.5, 0.0);  // Đỉnh trái trên
		glEnd();
	}

	// Vẽ tường
	void drawWall() { 
		//loadTexture("data/bricks.bmp");

		// Vẽ tường phía trước
		glPushMatrix();
		glTranslatef(0.0f, 5.0f, 10.0f);
		glScaled(20, 10, 0);
		settingWall();
		glPopMatrix();

		// Vẽ tường phía sau
		glPushMatrix();
		glTranslatef(0.0f, 5.0f, -10.0f);
		glScaled(20, 10, 0);
		settingWall();
		glPopMatrix();

		// Vẽ tường bên trái
		glPushMatrix();
		glTranslatef(-10.0f, 5.0f, 0.0f);
		glRotated(90.0, 0, 1.0, 0);
		glScaled(20, 10, 0);
		settingWall();
		glPopMatrix();

		// Vẽ tường bên phải
		glPushMatrix();
		glTranslatef(10.0f, 5.0f, 0.0f);
		glRotated(90.0, 0, 1.0, 0);
		glScaled(20, 10, 0);
		settingWall();
		glPopMatrix();
	}

	// Vẽ bàn
	void drawTable() {
		// Vẽ mặt bàn
		glColor3f(0.5f, 0.35f, 0.05f); // Màu nâu cho mặt bàn
		glBegin(GL_QUADS);
			glVertex3f(-2.0f, 0.0f, -2.0f); // Góc trái dưới
			glVertex3f(-2.0f, 0.0f, 2.0f);  // Góc trái trên
			glVertex3f(2.0f, 0.0f, 2.0f);   // Góc phải trên
			glVertex3f(2.0f, 0.0f, -2.0f);  // Góc phải dưới
		glEnd();

		// Vẽ chân bàn
		glColor3f(0.5f, 0.35f, 0.05f); // Màu nâu cho chân bàn
		glBegin(GL_QUADS);
			// Chân 1
			glVertex3f(-1.8f, -1.5f, -1.8f); // Góc dưới bên trái
			glVertex3f(-1.8f, 0.0f, -1.8f);  // Góc trên bên trái
			glVertex3f(-1.6f, 0.0f, -1.8f);  // Góc trên bên phải
			glVertex3f(-1.6f, -1.5f, -1.8f); // Góc dưới bên phải

			// Chân 2
			glVertex3f(-1.8f, -1.5f, 1.8f); // Góc dưới bên trái
			glVertex3f(-1.8f, 0.0f, 1.8f);  // Góc trên bên trái
			glVertex3f(-1.6f, 0.0f, 1.8f);  // Góc trên bên phải
			glVertex3f(-1.6f, -1.5f, 1.8f); // Góc dưới bên phải

			// Chân 3
			glVertex3f(1.8f, -1.5f, 1.8f); // Góc dưới bên trái
			glVertex3f(1.8f, 0.0f, 1.8f);  // Góc trên bên trái
			glVertex3f(1.6f, 0.0f, 1.8f);  // Góc trên bên phải
			glVertex3f(1.6f, -1.5f, 1.8f); // Góc dưới bên phải

			// Chân 4
			glVertex3f(1.8f, -1.5f, -1.8f); // Góc dưới bên trái
			glVertex3f(1.8f, 0.0f, -1.8f);  // Góc trên bên trái
			glVertex3f(1.6f, 0.0f, -1.8f);  // Góc trên bên phải
			glVertex3f(1.6f, -1.5f, -1.8f); // Góc dưới bên phải
		glEnd();
	}

	// Vẽ Ghế
	void drawChair() {
		// Vẽ mặt ghế
		glColor3f(0.5f, 0.35f, 0.05f); // Màu nâu cho mặt ghế
		glBegin(GL_QUADS);
			glVertex3f(-1.0f, -1.0f, -1.0f); // Góc trái dưới
			glVertex3f(-1.0f, -1.0f, 1.0f);  // Góc trái trên
			glVertex3f(1.0f, -1.0f, 1.0f);   // Góc phải trên
			glVertex3f(1.0f, -1.0f, -1.0f);  // Góc phải dưới
		glEnd();

		// Vẽ chân ghế
		glColor3f(0.5f, 0.35f, 0.05f); // Màu nâu cho chân ghế
		glBegin(GL_QUADS);
			// Chân 1
			glVertex3f(-0.9f, -2.0f, -0.9f); // Góc dưới bên trái 
			glVertex3f(-0.9f, -1.0f, -0.9f); // Góc trên bên trái
			glVertex3f(-0.7f, -1.0f, -0.9f); // Góc trên bên phải
			glVertex3f(-0.7f, -2.0f, -0.9f); // Góc dưới bên phải 

			// Chân 2
			glVertex3f(-0.9f, -2.0f, 0.9f); // Góc dưới bên trái 
			glVertex3f(-0.9f, -1.0f, 0.9f); // Góc trên bên trái
			glVertex3f(-0.7f, -1.0f, 0.9f); // Góc trên bên phải
			glVertex3f(-0.7f, -2.0f, 0.9f); // Góc dưới bên phải 

			// Chân 3
			glVertex3f(0.9f, -2.0f, 0.9f); // Góc dưới bên trái 
			glVertex3f(0.9f, -1.0f, 0.9f); // Góc trên bên trái
			glVertex3f(0.7f, -1.0f, 0.9f); // Góc trên bên phải
			glVertex3f(0.7f, -2.0f, 0.9f); // Góc dưới bên phải 

			// Chân 4
			glVertex3f(0.9f, -2.0f, -0.9f); // Góc dưới bên trái
			glVertex3f(0.9f, -1.0f, -0.9f); // Góc trên bên trái
			glVertex3f(0.7f, -1.0f, -0.9f); // Góc trên bên phải
			glVertex3f(0.7f, -2.0f, -0.9f); // Góc dưới bên phải 
		glEnd();

		// Vẽ lưng ghế
		glColor3f(0.5f, 0.35f, 0.05f); // Màu nâu cho lưng ghế
		glBegin(GL_QUADS);
			glVertex3f(-1.0f, -1.0f, 1.0f);  // Góc dưới bên trái
			glVertex3f(-1.0f, 1.0f, 1.0f);   // Góc trên bên trái
			glVertex3f(1.0f, 1.0f, 1.0f);    // Góc trên bên phải
			glVertex3f(1.0f, -1.0f, 1.0f);   // Góc dưới bên phải
		glEnd();
	}

	// Vẽ tủ quần áo
	void drawWardrobe() {
		// Vẽ thân tủ
		glColor3f(0.55f, 0.27f, 0.07f); // Màu nâu cho tủ
		glBegin(GL_QUADS);
			// Mặt trước
			glVertex3f(-1.0f, 0.0f, 4.0f); // Góc trái dưới
			glVertex3f(-1.0f, 3.0f, 4.0f); // Góc trái trên
			glVertex3f(1.0f, 3.0f, 4.0f);  // Góc phải trên
			glVertex3f(1.0f, 0.0f, 4.0f);  // Góc phải dưới

			// Mặt sau
			glVertex3f(-1.0f, 0.0f, 2.5f); // Góc trái dưới
			glVertex3f(-1.0f, 3.0f, 2.5f); // Góc trái trên
			glVertex3f(1.0f, 3.0f, 2.5f);  // Góc phải trên
			glVertex3f(1.0f, 0.0f, 2.5f);  // Góc phải dưới

			// Mặt trái
			glVertex3f(-1.0f, 0.0f, 2.5f); // Góc trái dưới
			glVertex3f(-1.0f, 3.0f, 2.5f); // Góc trái trên
			glVertex3f(-1.0f, 3.0f, 4.0f); // Góc phải trên
			glVertex3f(-1.0f, 0.0f, 4.0f); // Góc phải dưới

			// Mặt phải
			glVertex3f(1.0f, 0.0f, 2.5f); // Góc trái dưới
			glVertex3f(1.0f, 3.0f, 2.5f); // Góc trái trên
			glVertex3f(1.0f, 3.0f, 4.0f); // Góc phải trên
			glVertex3f(1.0f, 0.0f, 4.0f); // Góc phải dưới

			// Mặt trên
			glVertex3f(-1.0f, 3.0f, 2.5f); // Góc trái dưới
			glVertex3f(1.0f, 3.0f, 2.5f);  // Góc trái trên
			glVertex3f(1.0f, 3.0f, 4.0f);  // Góc phải trên
			glVertex3f(-1.0f, 3.0f, 4.0f); // Góc phải dưới

			// Mặt dưới
			glVertex3f(-1.0f, 0.0f, 2.5f); // Góc trái dưới
			glVertex3f(1.0f, 0.0f, 2.5f);  // Góc trái trên
			glVertex3f(1.0f, 0.0f, 4.0f);  // Góc phải trên
			glVertex3f(-1.0f, 0.0f, 4.0f); // Góc phải dưới
		glEnd();

		// Vẽ cửa tủ bên trái
		glColor3f(0.6f, 0.3f, 0.1f); // Màu nâu nhạt hơn cho cửa tủ
		glBegin(GL_QUADS);
			glVertex3f(-1.0f, 0.0f, 4.01f); // Góc trái dưới
			glVertex3f(-1.0f, 3.0f, 4.01f); // Góc trái trên
			glVertex3f(0.0f, 3.0f, 4.01f);  // Góc phải trên
			glVertex3f(0.0f, 0.0f, 4.01f);  // Góc phải dưới
		glEnd();

		// Vẽ cửa tủ bên phải
		glColor3f(0.6f, 0.3f, 0.1f); // Màu nâu nhạt hơn cho cửa tủ
		glBegin(GL_QUADS);
			glVertex3f(0.0f, 0.0f, 4.01f); // Góc trái dưới
			glVertex3f(0.0f, 3.0f, 4.01f); // Góc trái trên
			glVertex3f(1.0f, 3.0f, 4.01f);  // Góc phải trên
			glVertex3f(1.0f, 0.0f, 4.01f);  // Góc phải dưới
		glEnd();

		// Vẽ tay nắm cửa tủ bên trái
		glColor3f(0.8f, 0.8f, 0.8f); // Màu xám cho tay nắm cửa
		glBegin(GL_QUADS);
			glVertex3f(-0.95f, 1.5f, 4.02f); // Góc trái dưới
			glVertex3f(-0.95f, 1.6f, 4.02f); // Góc trái trên
			glVertex3f(-0.85f, 1.6f, 4.02f); // Góc phải trên
			glVertex3f(-0.85f, 1.5f, 4.02f); // Góc phải dưới
		glEnd();

		// Vẽ tay nắm cửa tủ bên phải
		glColor3f(0.8f, 0.8f, 0.8f); // Màu xám cho tay nắm cửa
		glBegin(GL_QUADS);
			glVertex3f(0.85f, 1.5f, 4.02f); // Góc trái dưới
			glVertex3f(0.85f, 1.6f, 4.02f); // Góc trái trên
			glVertex3f(0.95f, 1.6f, 4.02f); // Góc phải trên
			glVertex3f(0.95f, 1.5f, 4.02f); // Góc phải dưới
		glEnd();

		// Vẽ đường kẻ ngăn cách giữa hai cánh tủ
		glColor3f(0.0f, 0.0f, 0.0f); // Màu đen cho đường kẻ ngăn cách
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 4.03f); // Điểm dưới
			glVertex3f(0.0f, 3.0f, 4.03f); // Điểm trên
		glEnd();
	}

	void drawBedFrame() {
		// Vẽ khung giường
		glColor3f(0.5, 0.35, 0.05); // Màu nâu
		glPushMatrix();
		glTranslatef(0.0f, 0.2f, 0.0f); // Dịch chuyển khung lên trên mặt đất
		glScalef(6.0f, 0.4f, 4.0f); // Kích thước khung
		glutSolidCube(0.5); // Vẽ hình lập phương
		glPopMatrix();
	}

	void drawMattress() {
		// Vẽ đệm giường
		glColor3f(0.9, 0.9, 0.9); // Màu trắng
		glPushMatrix();
		glTranslatef(0.0f, 0.25f, 0.0f); // Dịch chuyển đệm lên trên khung
		glScalef(5.6f, 0.8f, 3.2f); // Kích thước đệm
		glutSolidCube(0.5); // Vẽ hình lập phương
		glPopMatrix();
	}

	void drawPillow() {
		// Vẽ mặt trên của gối
		glColor3f(0.5, 0.5, 0.5); // Màu trắng
			glBegin(GL_QUADS);
			glVertex3f(-1.0, 0.0, -1.0); // Đỉnh trái dưới
			glVertex3f(1.0, 0.0, -1.0);  // Đỉnh phải dưới
			glVertex3f(1.0, 0.0, 1.0);   // Đỉnh phải trên
			glVertex3f(-1.0, 0.0, 1.0);  // Đỉnh trái trên
		glEnd();

		// Vẽ mặt dưới của gối
		glBegin(GL_QUADS);
			glVertex3f(-1.0, -0.5, -1.0); // Đỉnh trái dưới
			glVertex3f(1.0, -0.5, -1.0);  // Đỉnh phải dưới
			glVertex3f(1.0, -0.5, 1.0);   // Đỉnh phải trên
			glVertex3f(-1.0, -0.5, 1.0);  // Đỉnh trái trên
		glEnd();

		// Vẽ các mặt bên của gối
		glBegin(GL_QUADS);
			// Mặt bên trái
			glVertex3f(-1.0, 0.0, -1.0);
			glVertex3f(-1.0, 0.0, 1.0);
			glVertex3f(-1.0, -0.5, 1.0);
			glVertex3f(-1.0, -0.5, -1.0);

			// Mặt bên phải
			glVertex3f(1.0, 0.0, -1.0);
			glVertex3f(1.0, 0.0, 1.0);
			glVertex3f(1.0, -0.5, 1.0);
			glVertex3f(1.0, -0.5, -1.0);

			// Mặt bên trên
			glVertex3f(-1.0, 0.0, -1.0);
			glVertex3f(1.0, 0.0, -1.0);
			glVertex3f(1.0, -0.5, -1.0);
			glVertex3f(-1.0, -0.5, -1.0);

			// Mặt bên dưới
			glVertex3f(-1.0, 0.0, 1.0);
			glVertex3f(1.0, 0.0, 1.0);
			glVertex3f(1.0, -0.5, 1.0);
			glVertex3f(-1.0, -0.5, 1.0);
		glEnd();
	}

	void drawBed() {
		drawBedFrame();
		drawMattress();
	}

	// Hàm vẽ cánh quạt
	void drawFanBlade() {
		// Vẽ cánh quạt
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 0.0f);    // Đỉnh trung tâm
		glVertex3f(0.2f, 0.5f, 0.0f);    // Đỉnh trên
		glVertex3f(0.2f, 0.0f, 0.0f);    // Đỉnh dưới
		glEnd();
	}
	// Hàm vẽ thân quạt
	void drawFanBody() {
		// Vẽ thân quạt
		glBegin(GL_QUADS);
		glVertex3f(-0.05f, -0.5f, -0.05f);   // Đỉnh trái dưới
		glVertex3f(0.05f, -0.5f, -0.05f);    // Đỉnh phải dưới
		glVertex3f(0.05f, 0.5f, -0.05f);     // Đỉnh phải trên
		glVertex3f(-0.05f, 0.5f, -0.05f);    // Đỉnh trái trên

		glVertex3f(-0.05f, -0.5f, 0.05f);   // Đỉnh trái dưới
		glVertex3f(0.05f, -0.5f, 0.05f);    // Đỉnh phải dưới
		glVertex3f(0.05f, 0.5f, 0.05f);     // Đỉnh phải trên
		glVertex3f(-0.05f, 0.5f, 0.05f);    // Đỉnh trái trên

		glVertex3f(-0.05f, -0.5f, -0.05f);   // Đỉnh trái dưới
		glVertex3f(-0.05f, 0.5f, -0.05f);    // Đỉnh trái trên
		glVertex3f(-0.05f, 0.5f, 0.05f);     // Đỉnh phải trên
		glVertex3f(-0.05f, -0.5f, 0.05f);    // Đỉnh phải dưới

		glVertex3f(0.05f, -0.5f, -0.05f);   // Đỉnh trái dưới
		glVertex3f(0.05f, 0.5f, -0.05f);    // Đỉnh phải trên
		glVertex3f(0.05f, 0.5f, 0.05f);     // Đỉnh phải dưới
		glVertex3f(0.05f, -0.5f, 0.05f);    // Đỉnh trái trên
		glEnd();
	}
	// Hàm vẽ cánh quạt
	void drawFanBlades() {
		// Vẽ cánh quạt
		glColor3f(0.3, 0.3, 0.3);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 0.0f);    // Đỉnh trung tâm
		glVertex3f(0.2f, 0.5f, 0.0f);    // Đỉnh trên
		glVertex3f(0.2f, 0.0f, 0.0f);    // Đỉnh dưới
		glEnd();
	}
	// Hàm vẽ đế quạt
	void drawFanBase() {
		// Vẽ đế quạt
		glBegin(GL_QUADS);
		// Mặt dưới
		glVertex3f(-0.2f, -0.1f, 0.2f);   // Đỉnh trái dưới
		glVertex3f(0.2f, -0.1f, 0.2f);    // Đỉnh phải dưới
		glVertex3f(0.2f, -0.1f, -0.2f);   // Đỉnh phải trên
		glVertex3f(-0.2f, -0.1f, -0.2f);  // Đỉnh trái trên
		// Mặt trên
		glVertex3f(-0.2f, 0.1f, -0.2f);   // Đỉnh trái dưới
		glVertex3f(0.2f, 0.1f, -0.2f);    // Đỉnh phải dưới
		glVertex3f(0.2f, 0.1f, 0.2f);     // Đỉnh phải trên
		glVertex3f(-0.2f, 0.1f, 0.2f);    // Đỉnh trái trên
		// Mặt trái
		glVertex3f(-0.2f, -0.1f, -0.2f);  // Đỉnh trái dưới
		glVertex3f(-0.2f, -0.1f, 0.2f);   // Đỉnh phải dưới
		glVertex3f(-0.2f, 0.1f, 0.2f);    // Đỉnh phải trên
		glVertex3f(-0.2f, 0.1f, -0.2f);   // Đỉnh trái trên
		// Mặt phải
		glVertex3f(0.2f, -0.1f, 0.2f);    // Đỉnh trái dưới
		glVertex3f(0.2f, -0.1f, -0.2f);   // Đỉnh phải dưới
		glVertex3f(0.2f, 0.1f, -0.2f);    // Đỉnh phải trên
		glVertex3f(0.2f, 0.1f, 0.2f);     // Đỉnh trái trên
		glEnd();
	}
	// Hàm vẽ quạt máy
	void drawFan() {
		// Vẽ thân quạt
		drawFanBody();

		// Vẽ cánh quạt
		for (int i = 0; i < 4; ++i) {
			glPushMatrix();
			glRotatef(i * 90.0f, 0.0f, 0.0f, 1.0f);
			drawFanBlades();
			glPopMatrix();
		}
	}

	// Hàm vẽ quạt trần
	void drawCeilingFan() {
		// Vẽ thân quạt
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glScalef(0.5f, 0.5f, 0.5f);
		glColor3f(0.8f, 0.8f, 0.8f);
		//gluCylinder(gluNewQuadric(), 0.2f, 0.5f, 20, 1);
		glPopMatrix();

		// Vẽ cánh quạt
		for (int i = 0; i < 3; i++) {
			glPushMatrix();
			glRotatef(i * 120.0f, 0.0f, 1.0f, 0.0f);
			glTranslatef(0.0f, 0.7f, 0.0f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.8f, 0.2f, 0.1f);
			glColor3f(0.2f, 0.2f, 0.2f);
			glutSolidCube(1.0f);
			glPopMatrix();
		}
	}

	// Hàm vẽ một hộp đơn giản
	void drawFridge(float width, float height, float depth) {
		// Mặt trước
		glBegin(GL_QUADS);
		glVertex3f(-width / 2, -height / 2, depth / 2);
		glVertex3f(width / 2, -height / 2, depth / 2);
		glVertex3f(width / 2, height / 2, depth / 2);
		glVertex3f(-width / 2, height / 2, depth / 2);
		glEnd();

		// Mặt sau
		glBegin(GL_QUADS);
		glVertex3f(-width / 2, -height / 2, -depth / 2);
		glVertex3f(-width / 2, height / 2, -depth / 2);
		glVertex3f(width / 2, height / 2, -depth / 2);
		glVertex3f(width / 2, -height / 2, -depth / 2);
		glEnd();

		// Mặt trên
		glBegin(GL_QUADS);
		glVertex3f(-width / 2, height / 2, -depth / 2);
		glVertex3f(-width / 2, height / 2, depth / 2);
		glVertex3f(width / 2, height / 2, depth / 2);
		glVertex3f(width / 2, height / 2, -depth / 2);
		glEnd();

		// Mặt dưới
		glBegin(GL_QUADS);
		glVertex3f(-width / 2, -height / 2, -depth / 2);
		glVertex3f(width / 2, -height / 2, -depth / 2);
		glVertex3f(width / 2, -height / 2, depth / 2);
		glVertex3f(-width / 2, -height / 2, depth / 2);
		glEnd();

		// Mặt bên trái
		glBegin(GL_QUADS);
		glVertex3f(-width / 2, -height / 2, -depth / 2);
		glVertex3f(-width / 2, -height / 2, depth / 2);
		glVertex3f(-width / 2, height / 2, depth / 2);
		glVertex3f(-width / 2, height / 2, -depth / 2);
		glEnd();

		// Mặt bên phải
		glBegin(GL_QUADS);
		glVertex3f(width / 2, -height / 2, -depth / 2);
		glVertex3f(width / 2, height / 2, -depth / 2);
		glVertex3f(width / 2, height / 2, depth / 2);
		glVertex3f(width / 2, -height / 2, depth / 2);
		glEnd();
	}
	void drawDoorHandle() {
		// Bắt đầu vẽ
		glBegin(GL_QUADS);

		// Mặt trước của tay nắm
		glVertex3f(0.05f, -0.05f, 0.1f);
		glVertex3f(0.05f, 0.05f, 0.1f);
		glVertex3f(0.15f, 0.05f, 0.1f);
		glVertex3f(0.15f, -0.05f, 0.1f);

		// Mặt trên của tay nắm
		glVertex3f(0.05f, 0.05f, 0.1f);
		glVertex3f(0.05f, 0.05f, 0.2f);
		glVertex3f(0.15f, 0.05f, 0.2f);
		glVertex3f(0.15f, 0.05f, 0.1f);

		// Mặt dưới của tay nắm
		glVertex3f(0.05f, -0.05f, 0.1f);
		glVertex3f(0.05f, -0.05f, 0.2f);
		glVertex3f(0.15f, -0.05f, 0.2f);
		glVertex3f(0.15f, -0.05f, 0.1f);

		// Mặt phía sau của tay nắm
		glVertex3f(0.05f, -0.05f, 0.2f);
		glVertex3f(0.05f, 0.05f, 0.2f);
		glVertex3f(0.15f, 0.05f, 0.2f);
		glVertex3f(0.15f, -0.05f, 0.2f);

		// Mặt bên trái của tay nắm
		glVertex3f(0.05f, -0.05f, 0.1f);
		glVertex3f(0.05f, -0.05f, 0.2f);
		glVertex3f(0.05f, 0.05f, 0.2f);
		glVertex3f(0.05f, 0.05f, 0.1f);

		// Mặt bên phải của tay nắm
		glVertex3f(0.15f, -0.05f, 0.1f);
		glVertex3f(0.15f, -0.05f, 0.2f);
		glVertex3f(0.15f, 0.05f, 0.2f);
		glVertex3f(0.15f, 0.05f, 0.1f);

		// Kết thúc vẽ
		glEnd();
	}

	// Hàm khởi tạo
	void init() {
		trans.x = 0;
		trans.y = 0;
		trans.z = 0;

		nPoints = 3;
		angle = 0;

		model1.nVertices = 4;
		model1.vertices[0] = point3(-0.5, -0.5, 0);
		model1.vertices[1] = point3(-0.5, 0, 0.5);
		model1.vertices[2] = point3(-0.5, 0.5, 0);
		model1.vertices[3] = point3(0.5, -0.5, 0);
		model1.nEdges = 6;
		model1.edges[0][0] = 0;
		model1.edges[0][1] = 1;
		model1.edges[1][0] = 1;
		model1.edges[1][1] = 2;
		model1.edges[2][0] = 2;
		model1.edges[2][1] = 3;
		model1.edges[3][0] = 3;
		model1.edges[3][1] = 0;
		model1.edges[4][0] = 2;
		model1.edges[4][1] = 0;
		model1.edges[5][0] = 3;
		model1.edges[5][1] = 1;

		model = &model1;
		glClearColor(1.0, 1.0, 1.0, 1.0);

	}

	// Vẽ sàn
	void drawGroundLines() {
		glColor3f(0.256f, 0.5f, 0.9f); // Màu cho lưới
		glBegin(GL_LINES);

		// Vẽ các đường dọc
		for (int i = -10; i <= 10; ++i) {
			glVertex3f((float)i, 0.0f, -10.0f);
			glVertex3f((float)i, 0.0f, 10.0f);
		}

		// Vẽ các đường ngang
		for (int i = -10; i <= 10; ++i) {
			glVertex3f(-10.0f, 0.0f, (float)i);
			glVertex3f(10.0f, 0.0f, (float)i);
		}

		glEnd();
	}

	// Hàm chỉ định
	void display1() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		float lx = sinf(cameraYaw * PI / 180.0f);
		float lz = -cosf(cameraYaw * PI / 180.0f);

		gluLookAt(cameraX, cameraY, cameraZ,
			cameraX + lx, cameraY, cameraZ + lz,
			0.0f, 1.0f, 0.0f);

		// Vẽ tường
		drawWall();

		// Vẽ mặt sàn
		glColor3f(0.0, 0.0, 0.0);
		drawGroundLines();

		// Vẽ bàn
		glPushMatrix();
		glTranslatef(0.0f, 1.5f, 0.0f);
		glRotated(90, 0.0f, 1.0f, 0.0f);// Dịch chuyển bàn lên trên một chút so với mặt sàn
		drawTable(); // Vẽ bàn
		glPopMatrix();
		// drawModelLines(model, trans); // vẽ đa giác


		// Đặt ghế cạnh bàn
		glPushMatrix();
		glTranslatef(0.0f, 2.0f, 1.0f); // Dịch chuyển ghế đến vị trí đối diện bàn
		drawChair(); // Vẽ ghế
		glPopMatrix();

		// Đặt tủ quần áo cách bàn ghế một khoảng cách
		glPushMatrix();
		glTranslatef(12.5f, 0.0f, 5.0f); // Điều chỉnh tọa độ theo ý muốn
		glRotated(-90.0, 0, 1.0, 0);
		drawWardrobe();
		glPopMatrix();

		// Đặt giường cạnh tủ quần áo
		glPushMatrix();
		glTranslatef(8.0f, 0.0f, 9.0f); // Điều chỉnh tọa độ theo ý muốn
		drawBed();
		glPopMatrix();

		// Đặt giường cạnh tủ quần áo
		glPushMatrix();
		glTranslatef(8.0f, 0.0f, 7.0f); // Điều chỉnh tọa độ theo ý muốn
		drawBed();
		glPopMatrix();

		// Đặt gối lên giường
		glPushMatrix();
		glTranslatef(9.0f, 0.6f, 7.0f);
		glScaled(0.2, 0.2, 0.6);
		drawPillow();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(9.0f, 0.6f, 9.0f);
		glScaled(0.2, 0.2, 0.6);
		drawPillow();
		glPopMatrix();

		// Đặt quạt
		glPushMatrix();
		glTranslatef(0.0f, 1.0f, -5.0f);
		drawFan();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 0.5f, -5.0f);
		drawFanBase();
		glPopMatrix();

		// Đặt quạt trần
		glPushMatrix();
		glTranslatef(0.0f, 4.0f, 0.0f);
		glScaled(2.5, 2.5, 2.5);
		drawCeilingFan();
		glPopMatrix();

		// Đặt tủ lạnh
		glPushMatrix();
		glTranslatef(-6.0f, 0.8f, -9.0f); // Di chuyển tủ lạnh về phía trước để hiển thị rõ hơn
		glScaled(1, 0.4, 1);
		drawFridge(2.0, 4.0, 2.0); // Kích thước tủ lạnh: rộng 2.0, cao 4.0, sâu 2.0
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-6.0f, 2.45f, -9.0f); // Di chuyển tủ lạnh về phía trước để hiển thị rõ hơn
		glScaled(1, 0.4, 1);
		drawFridge(2.0, 4.0, 2.0); // Kích thước tủ lạnh: rộng 2.0, cao 4.0, sâu 2.0
		glPopMatrix();

		// Đặt vách ngăn giữa 2 khay tủ lạnh
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(-6.0f, 1.6f, -9.0f); // Di chuyển tủ lạnh về phía trước để hiển thị rõ hơn
		glScaled(1, 0.02, 1);
		drawFridge(2.0, 4.0, 2.0); // Kích thước tủ lạnh: rộng 2.0, cao 4.0, sâu 2.0
		glPopMatrix();

		// Đặt tay nắm cửa tủ lạnh
		glColor3f(0.8f, 0.8f, 0.8f);
		glPushMatrix();
		glTranslatef(-7.0f, 2.8f, -8.1f);
		glScaled(1, 6, 1);
		drawDoorHandle();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-7.0f, 1.1f, -8.1f);
		glScaled(1, 6, 1);
		drawDoorHandle();
		glPopMatrix();

		glFlush();

		if (rotate) {
			angle = angle + 0.0005;
			regularPolygon(model, 0.5, nPoints, angle);
		}
	}

	void processKeys(unsigned char key, int xx, int yy) {
		switch (key) {
		case 'w':
			cameraX += sinf(cameraYaw * PI / 180.0f) * 0.1f;
			cameraZ -= cosf(cameraYaw * PI / 180.0f) * 0.1f;
			break;
		case 's':
			cameraX -= sinf(cameraYaw * PI / 180.0f) * 0.1f;
			cameraZ += cosf(cameraYaw * PI / 180.0f) * 0.1f;
			break;
		case 'a':
			cameraX -= cosf(cameraYaw * PI / 180.0f) * 0.1f;
			cameraZ -= sinf(cameraYaw * PI / 180.0f) * 0.1f;
			break;
		case 'd':
			cameraX += cosf(cameraYaw * PI / 180.0f) * 0.1f;
			cameraZ += sinf(cameraYaw * PI / 180.0f) * 0.1f;
			break;
		case 'r':
			rotate = !rotate;
			break;
		case '>':
			nPoints++;
			regularPolygon(model, 0.5, nPoints);
			break;
		case '<':
			nPoints--;
			if (nPoints < 3) nPoints = 3;
			regularPolygon(model, 0.5, nPoints);
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}

	void processMouse(int button, int state, int xx, int yy) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			glutPostRedisplay();
		}
	}

	void changeSize(int w, int h) {
		if (h == 0) h = 1;
		float ratio = w * 1.0 / h;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, ratio, 0.1f, 100.0f); // Chỉnh lại góc nhìn để phù hợp hơn với 3D

		glMatrixMode(GL_MODELVIEW);
	}
};

int foor(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Sửa lại để bật GL_DEPTH

	// Lấy kích thước màn hình
	int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowSize(screenWidth, screenHeight); // Sử dụng kích thước màn hình
	glutInitWindowPosition(0, 0); // Đặt cửa sổ ở góc trên cùng bên trái của màn hình

	glutCreateWindow("3D Room Simulation");

	Foor::init();
	glutReshapeFunc(Foor::changeSize);
	glutDisplayFunc(Foor::display1);
	glutKeyboardFunc(Foor::processKeys);
	glutMouseFunc(Foor::processMouse);
	glutSpecialFunc(Foor::processSpecialKeys);
	glutIdleFunc(Foor::display1);

	glEnable(GL_DEPTH_TEST); // Bật kiểm tra độ sâu

	glutMainLoop();

	free(Foor::model);
	return 0;
}