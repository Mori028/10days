#include "ElementH.h"
#include "map.h"

ElementH::ElementH()
{
}

ElementH::~ElementH()
{
	//delete elementH_;
	//delete elementModel_;
}

void ElementH::Initialize(Model* elementModel, Vector3 elementPos, int connectMaxNmb, int elementNmb, Input* input, int map)
{
	assert(input);
	assert(elementModel);
	input_ = input;
	elementNmb_ = elementNmb;
	elementModel_ = elementModel;
	elementH_ = Object3d::Create();
	elementH_->wtf.position = elementPos;
	place.x = elementH_->wtf.position.x;
	place.y = -elementH_->wtf.position.y;
	//マップ更新
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (map == 0) {
				baseMap[j][i] = tutorialMap[j][i];
			}
			else if (map == 1) {
				baseMap[j][i] = map1[j][i];
			}
			else if (map == 2) {
				baseMap[j][i] = map2[j][i];
			}
		}
	}
	elementH_->SetModel(elementModel_);
	connectMaxNum_ = connectMaxNmb;
	for (int i = 0; i < 3; i++) {
		collectKinds[i] = { elementNmb_ };
	}

	worldPosition.x = (float)place.x;
	worldPosition.y = -(float)place.y;
	position.x = worldPosition.x + moveVal - easeOutCubic(frame / maxframe) * moveVal;
	position.y = worldPosition.y + moveVal - easeOutCubic(frame / maxframe) * moveVal;
	intFlame = 0;
}

void ElementH::Update(Vector3 playerPos, bool hitBlocks)
{
	Vector3 playyerPos = playerPos;
	move = { 0,0,0 };

	if (ifConnect) {

		if (intFlame >= maxframe) {
			if (hitBlocks == false) {
				if (frame >= maxframe) {
					if (hitElement == false) {
						moveOn = false;
						if (input_->PushKey(DIK_A) && place.x > 0) {
							if (baseMap[(int)place.y][(int)place.x - 1] == 0) {
								direction = Direction::Left;
								worldPosition.x -= moveVal;
								place.x--;
								frame = 0;
								moveOn = true;
							}
						}
						else if (input_->PushKey(DIK_D) && place.x < 5) {
							if (baseMap[(int)place.y][(int)place.x + 1] == 0) {
								direction = Direction::Right;
								worldPosition.x += moveVal;
								place.x++;
								frame = 0;
								moveOn = true;
							}
						}

						else if (input_->PushKey(DIK_W) && place.y > 0) {
							if (baseMap[(int)place.y - 1][(int)place.x] == 0) {
								direction = Direction::Up;
								worldPosition.y += moveVal;
								place.y--;
								frame = 0;
								moveOn = true;
							}
						}
						else if (input_->PushKey(DIK_S) && place.y < 5) {
							if (baseMap[(int)place.y + 1][(int)place.x] == 0) {
								direction = Direction::Down;
								worldPosition.y -= moveVal;
								place.y++;
								frame = 0;
								moveOn = true;

							}
						}
					}

				}

				//移動にイージングを掛ける
				if (direction == Direction::Left) {
					position.x = worldPosition.x + moveVal - easeOutCubic(frame / maxframe) * moveVal;
				}
				else if (direction == Direction::Right) {
					position.x = worldPosition.x - moveVal + easeOutCubic(frame / maxframe) * moveVal;
				}
				else if (direction == Direction::Up) {
					position.y = worldPosition.y - moveVal + easeOutCubic(frame / maxframe) * moveVal;
				}
				else if (direction == Direction::Down) {
					position.y = worldPosition.y + moveVal - easeOutCubic(frame / maxframe) * moveVal;
				}
			}
		}
	}
	if (connectNmb_ >= connectMaxNum_) {
		connectMax_ = true;
	}
	hitElement = false;
	elementH_->wtf.position = position;
	elementH_->Update();
	//oldPlayerPos_ = playyerPos;

}

void ElementH::Draw()
{
	elementH_->Draw();
}

void ElementH::collectNmb(int Nmb)
{

	if (collectKinds[0] == elementNmb_ && elementNmb_ != Nmb) {
		collectKinds[0] = Nmb;
		connectNmb_++;
		ifConnect = true;
	}
	else if (collectKinds[1] == elementNmb_ && elementNmb_ != Nmb && collectKinds[0] != Nmb) {
		collectKinds[1] = Nmb;
		connectNmb_++;
	}
	else if (collectKinds[2] == elementNmb_ && elementNmb_ != Nmb && collectKinds[0] != Nmb && collectKinds[1] != Nmb) {
		collectKinds[2] = Nmb;
		connectNmb_++;
	}


}

void ElementH::WallUpdate(bool elementHit)
{
	if (ifConnect) {
			if (intFlame <= maxframe) {
				intFlame += oneframe;
			}
			if (intFlame >= maxframe) {
				//イージング用フレーム
				if (frame < maxframe) {
					frame += oneframe;
				}
				else {
					frame = maxframe;
				}

				if (frame >= maxframe) {
					hitBlock = false;
					if (input_->PushKey(DIK_A) && place.x > 0) {
						if (baseMap[(int)place.y][(int)place.x - 1] == 0) {
							hitBlock = false;
						}
						else if (baseMap[(int)place.y][(int)place.x - 1] == 1) {
							hitBlock = true;
						}
					}
					else if (input_->PushKey(DIK_D) && place.x < 5) {
						if (baseMap[(int)place.y][(int)place.x + 1] == 0) {
							hitBlock = false;
						}
						else if (baseMap[(int)place.y][(int)place.x + 1] == 1) {
							hitBlock = true;
						}
					}

					else if (input_->PushKey(DIK_W) && place.y > 0) {
						if (baseMap[(int)place.y - 1][(int)place.x] == 0) {
							hitBlock = false;
						}
						else if (baseMap[(int)place.y - 1][(int)place.x] == 1) {
							hitBlock = true;
						}
					}
					else if (input_->PushKey(DIK_S) && place.y < 5) {
						if (baseMap[(int)place.y + 1][(int)place.x] == 0) {
							hitBlock = false;

						}
						else if (baseMap[(int)place.y + 1][(int)place.x] == 1) {
							hitBlock = true;
						}
					}
					//範囲外判定
					if (input_->PushKey(DIK_A) && place.x <= 0) {
						hitBlock = true;
					}
					else if (input_->PushKey(DIK_D) && place.x >= 5) {
						hitBlock = true;
					}

					else if (input_->PushKey(DIK_W) && place.y <= 0) {
						hitBlock = true;
					}
					else if (input_->PushKey(DIK_S) && place.y >= 5) {
						hitBlock = true;
					}
				}
		}
	}
}






