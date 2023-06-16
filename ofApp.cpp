#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofSetLineWidth(1.5);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto radius = 10;
	auto number = 9;
	auto len = 30;
	for (int i = 0; i < number; i++) {

		auto x_min = 240 * (i % 3) - 360;
		auto x_max = 240 * (i % 3) - 120;

		auto y_min = 240 * (i / 3) - 360;
		auto y_max = 240 * (i / 3) - 120;

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		for (int k = 0; k < len; k++) {

			auto location = glm::vec2(
				ofMap(ofNoise(noise_seed.x * 0.03, ofGetFrameNum() * 0.02 + k * 0.02), 0, 1, x_min + 10, x_max - 10),
				ofMap(ofNoise(noise_seed.y * 0.03, ofGetFrameNum() * 0.02 + k * 0.02), 0, 1, y_min + 10, y_max - 10));
			auto next_location = glm::vec2(
				ofMap(ofNoise(noise_seed.x * 0.03, ofGetFrameNum() * 0.02 + k * 0.02 + 0.002), 0, 1, x_min + 10 , x_max - 10),
				ofMap(ofNoise(noise_seed.y * 0.03, ofGetFrameNum() * 0.02 + k * 0.02 + 0.002), 0, 1, y_min + 10, y_max - 10));

			auto deg = atan2(next_location.y - location.y, next_location.x - location.x) * RAD_TO_DEG;

			ofPushMatrix();
			ofTranslate(location);
			ofRotate(deg);

			ofColor color;
			color.setHsb(ofMap(i, 0, number, 0, 255), 180, 255);
			ofSetColor(color, ofMap(k, 0, len, 32, 255));
			ofNoFill();

			ofBeginShape();
			for (int d = -120; d <= 120; d += 120) {

				ofVertex(radius * cos(d * DEG_TO_RAD), radius * sin(d * DEG_TO_RAD));
			}
			ofEndShape(false);

			ofPopMatrix();

		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}