#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-bold.ttf", 500, true, true, true);
	this->fbo.allocate(ofGetWidth(), ofGetHeight());

	this->size = 30;
	for (int x = size * 0.5; x <= ofGetWidth() - size * 0.5; x += this->size) {

		for (int y = size * 0.5; y <= ofGetWidth() - size * 0.5; y += this->size) {

			this->box_list.push_back(make_pair(glm::vec3(x, y, 0), this->size));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->fbo.begin();
	ofClear(0);
	ofSetColor(39);

	string word = to_string((ofGetFrameNum() / 90) % 10);
	this->font.drawString(word, this->fbo.getWidth() * 0.5 - this->font.stringWidth(word) * 0.5, this->fbo.getHeight() * 0.5 + this->font.stringHeight(word) * 0.5);

	this->fbo.end();
	this->fbo.readToPixels(this->pixels);

	for (auto& box : this->box_list) {

		auto location = box.first;
		auto& height = box.second;

		if (this->pixels.getColor(location.x, location.y) != ofColor(0, 0)) {

			if (height < this->size * 5) {
			
				height += 2;
			}
		}
		else {

			if (height > this->size) {

				height -= 2;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofTranslate(ofGetWidth() * -0.5, ofGetHeight() * -0.5);

	for (auto& box : this->box_list) {

		auto location = box.first;
		auto height = box.second;

		ofFill();
		ofSetColor(ofMap(height, this->size, this->size * 5, 239, 39));
		ofDrawBox(location - glm::vec3(0, 0, height * 0.5), this->size - 1, this->size - 1, -height + 1);

		ofNoFill();
		ofSetColor(ofMap(height, this->size, this->size * 5, 39, 239));
		ofDrawBox(location - glm::vec3(0, 0, height * 0.5), this->size, this->size, -height);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}