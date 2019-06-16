void LoadAndShowMapTest::onEnter(){
	BasicScene::onEnter();
	auto size = Director::getInstance() -> getWinSize();
	//װ�ص�ͼ
	auto  map = TMXTiledMap::create(Tilemap/TileMap.tmx);
	//���ô�С
	map -> setScale(2) ;
	//����ê��Ϊ���ĵ�
	map -> setAnchorPoint(Point(0.5,0.5));
	//���õ�ͼ��λ��
	map -> setPosition(size.width/2,size.height/2) ;
	
	addChild(TileMap);
	
}
