#include "Arduino.h"
#include "Block.h"

// 테트리미노를 설정할 때 쓰이는 블록
Block empty3[3];
Block empty4[4];
Block empty(0, 0, 0, false, false);// empty
Block minoZ(1, 0, 0, true, true); // Z red
Block minoL(3, 1, 0, true, true); // L orange
Block minoO(1, 1, 0, true, true); // O yellow
Block minoS(0, 1, 0, true, true); // S green
Block minoI(0, 1, 1, true, true); // I sky
Block minoJ(0, 0, 1, true, true); // J blue
Block minoT(1, 0, 1, true, true); // T purple

// 게임판의 벽을 설정할 때 쓰이는 블록
Block wall(1, 1, 1, true, false);  // wall

// 테트리미노 I(i)를 나타내기 위한 배열
Block blockI[2][4][4] = {	// I(i) 모양 블록을 나타내는 배열, 2가지 방향, 4 * 4 배열
	{{empty, minoI, empty, empty}, {empty, minoI, empty, empty}, {empty, minoI, empty, empty}, {empty, minoI, empty, empty}}, 
	{empty4, {minoI, minoI, minoI, minoI}, empty4, empty4}
	
};
Block blocks[6][4][3][3] = {      // 6가지 모양(blockType), 4가지 방향(blockState), 3 * 3 배열
	// mino Z
	{{{empty, minoZ, empty}, {empty, minoZ, minoZ}, {empty, empty, minoZ}},
	{{empty, minoZ, minoZ}, {minoZ, minoZ, empty}, empty3},
	{{minoZ, empty, empty}, {minoZ, minoZ, empty}, {empty, minoZ, empty}},
	{empty3, {empty, minoZ, minoZ}, {minoZ, minoZ, empty}}},

	// mino L
	{{{empty, minoL, minoL}, {empty, minoL, empty}, {empty, minoL, empty}},
	{{minoL, empty, empty}, {minoL, minoL, minoL}, {empty, empty, empty}},
	{{empty, minoL, empty}, {empty, minoL, empty}, {minoL, minoL, empty}},
	{empty3, {minoL, minoL, minoL}, {empty, empty, minoL}}},

	// mino O
	{{empty3, {empty, minoO, minoO}, {empty, minoO, minoO}},
	{empty3, {empty, minoO, minoO}, {empty, minoO, minoO}},
	{empty3, {empty, minoO, minoO}, {empty, minoO, minoO}},
	{empty3, {empty, minoO, minoO}, {empty, minoO, minoO}}},

	// mino S
	{{{empty, empty, minoS}, {empty, minoS, minoS}, {empty, minoS, empty}},
	{empty3, {minoS, minoS, empty}, {empty, minoS, minoS}},
	{{empty, minoS, empty}, {minoS, minoS, empty}, {minoS, empty, empty}},
	{{minoS, minoS, empty}, {empty, minoS, minoS}, empty3}},

	// mino J
	{{{empty, minoJ, empty}, {empty, minoJ, empty}, {empty, minoJ, minoJ}},
	{{empty, empty, minoJ}, {minoJ, minoJ, minoJ}, empty3},
	{{minoJ, minoJ, empty}, {empty, minoJ, empty}, {empty, minoJ, empty}},
	{empty3, {minoJ, minoJ, minoJ}, {minoJ, empty, empty}}},

	// mino T
	{{{empty, minoT, empty}, {empty, minoT, minoT}, {empty, minoT, empty}},
	{empty3, {minoT, minoT, minoT}, {empty, minoT, empty}},
	{{empty, minoT, empty}, {minoT, minoT, empty}, {empty, minoT, empty}},
	{{empty, minoT, empty}, {minoT, minoT, minoT}, {empty, empty, empty}}}
};

Block::Block() {
	setBlock(0, 0, 0, false, false);
}	// default 생성자
Block::Block(uint8_t r, uint8_t g, uint8_t b, bool onOff, bool moving) {
	setBlock(r, g, b, onOff, moving);
}	// 생성자
void Block::setBlock(uint8_t r1, uint8_t g1, uint8_t b1, bool state, bool moveState) {
	r = r1;
	g = g1;
	b = b1;
	onOff = state;
	moving = moveState;
}	// Block 필드값 설정 및 생성에 쓰임
void Block::setLedOff() {
	setBlock(0, 0, 0, false, false);
}	// led 소등(실제로 꺼지지는 않고 onOff 값만 바꿔줌, 상태가 바뀌면 drawMain(ledTurn)에서 꺼줌)
void Block::ledTurn(int x, int y) {
	if(onOff) matrix.drawPixel(x, y, matrix.Color333(r, g, b));
	else matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));
}	// (외부에서 조절)(Block의 onOff 값이 변경되었다면) led를 끄거나 켜줌
bool Block::operator == (const Block & p) {
	if(r == p.r && g == p.g && b == p.g && onOff == p.onOff && moving == p.moving) return true;
	else return false;
}	// == operator overloading
bool Block::operator != (const Block & p) {
	if(r != p.r || g != p.g || b != p.g || onOff != p.onOff || moving != p.moving) return true;
	else return false;
}	// != operator overloading
Block& Block::operator = (const Block & p) {
	r = p.r, g = p.g, b = p.b;
	onOff = p.onOff;
	moving = p.moving;
	return *this;
}	// = operator overloading