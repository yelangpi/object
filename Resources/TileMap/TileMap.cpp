void LoadAndShowMapTest::onEnter(){
	BasicScene::onEnter();
	auto size = Director::getInstance() -> getWinSize();
	//装载地图
	auto  map = TMXTiledMap::create(Tilemap/TileMap.tmx);
	//设置大小
	map -> setScale(2) ;
	//设置锚点为中心点
	map -> setAnchorPoint(Point(0.5,0.5));
	//设置地图的位置
	map -> setPosition(size.width/2,size.height/2) ;
	
	addChild(TileMap);
	
}
