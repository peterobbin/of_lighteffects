#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{


	gravity.set( 0.0, 0.02 );
	shader.load( "bokeh.vert", "bokeh.frag" );
	flare.load( "flare.vert", "flare.frag" );
	stripes.load( "flareStripes.vert", "flareStripes.frag" );
	shaderBlurX.load( "blurx.vert", "blurx.frag" );
	shaderBlurY.load( "blury.vert", "blury.frag" );
	bloom.load( "bloom.vert", "bloom.frag" );

	timestamp = ofGetElapsedTimef();
	enableEffects = false;
	ofHideCursor();

	//
	//    bluramt = 0.0;
	//    bloomsize = 1.0;
	//    bloombrightness = 0.5;
	//    flareBarRange = 1.0;
	//    flareBarThickness = 1.0;
	//    flareStripeBlur = 1.0;
	//    flareStripeBrightness = 1.5;
	//    flareStripeSize = 1.0;
	//    bokehSides = 6;
	//    bokehSize = 1.0;


	gui.setup( "shader effects" );
	gui.add( showBokeh.set( "show Bokeh", true ) );
	gui.add( showFlareBar.set( "show FlareBar", true ) );
	gui.add( showFlareStripes.set( "show FlareStripes", true ) );
	gui.add( enableBlooms.set( "enable Blooms", true ) );
	gui.add( enableBlur.set( "enable Blur", true ) );


	gui.add( bokehSides.set( "bokeh sides", 6, 5, 10 ) );
	gui.add( bokehSize.set( "bokeh size", 1.0, 0.0, 2.0 ) );
	gui.add( flareBarRange.set( "flare bar range", 1.0, 0.0, 2.0 ) );
	gui.add( flareBarThickness.set( "flare bar thickness", 1.0, 0.0, 2.0 ) );
	gui.add( flareStripeBlur.set( "flare stripe blur", 1.0, 0.0, 2.0 ) );
	gui.add( flareStripeBrightness.set( "flare stripe brightness", 1.5, 0.0, 2.0 ) );
	gui.add( flareStripeSize.set( "flare stripe size", 1.0, 0.0, 2.0 ) );
	gui.add( bloomsize.set( "bloom size", 1.0, 0.0, 1.0 ) );
	gui.add( bloombrightness.set( "bloom brightness", 0.5, 0.0, 2.0 ) );
	gui.add( bluramt.set( "blur amount", 0.0, 0.0, 2.0 ) );




}

//--------------------------------------------------------------
void ofApp::update()
{
	windowSize = ofVec2f( ofGetWidth(), ofGetHeight() );
	circlePos = ofVec2f( sin( ofGetElapsedTimef() ) * 50 + ofGetWidth() / 2, cos( ofGetElapsedTimef() ) * 50 + ofGetHeight() / 2 );

	for( int i = 0; i < systems.size(); i++ ) {
		systems[i].update( gravity );
	}

	// normalized timer vlue
	timer = ofGetElapsedTimef() - timestamp;
	timer = 1.0 - ofClamp( timer, 0.0, 3.0 ) / 3.0;

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor( 0 );
    ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
	ofSetColor( 255 );
	ofBackground( 0 );
	ofEnableBlendMode( OF_BLENDMODE_ADD );
    
	if( enableEffects ) {
		if( showBokeh ) { bokeh(); };

		if( showFlareBar ) { flareBar(); }

		if( showFlareStripes ) { flareStripes(); }

		if( enableBlooms ) { blooms(); }

		if( enableBlur ) { blur( bluramt ); }
	}

	gui.draw();

	// pinpoint mouse location
	ofDrawCircle( mouseX, mouseY, 1.0 );


}

//-------------------------------------------
void ofApp::blooms()
{
	bloom.begin();
	bloom.setUniform2f( "u_resolution", ofGetWidth(), ofGetHeight() );
	bloom.setUniform1f( "u_time", ofGetElapsedTimef() );
	bloom.setUniform2f( "u_mouse", systemLocation.x, systemLocation.y );
	bloom.setUniform1f( "u_timer", timer );
	bloom.setUniform1f( "u_size", bloomsize );
	bloom.setUniform1f( "u_brightness", bloombrightness );


	ofDrawRectangle( 0, 0, ofGetWidth(), ofGetHeight() );
	bloom.end();
}

//-------------------------------------------
void ofApp::blur( float bluramt )
{
	image.grabScreen( 0, 0, ofGetWidth(), ofGetHeight() );
	fboBlurOnePass.allocate( image.getWidth(), image.getHeight() );
	fboBlurTwoPass.allocate( image.getWidth(), image.getHeight() );



	float blur = bluramt;

	// modified from oF blur tutorial
	// horizonal pass
	//----------------------------------------------------------
	fboBlurOnePass.begin();
	shaderBlurX.begin();
	shaderBlurX.setUniform1f( "blurAmnt", blur );
	image.draw( 0, 0 );
	shaderBlurX.end();
	fboBlurOnePass.end();

	// vertical pass
	//----------------------------------------------------------
	fboBlurTwoPass.begin();
	shaderBlurY.begin();
	shaderBlurY.setUniform1f( "blurAmnt", blur );
	fboBlurOnePass.draw( 0, 0 );
	shaderBlurY.end();
	fboBlurTwoPass.end();

	//----------------------------------------------------------
    ofSetColor( ofColor(0) );
	fboBlurTwoPass.draw( 0, 0 );


}



//-------------------------------------------
void ofApp::flareStripes()
{
	stripes.begin();
	stripes.setUniform2f( "u_resolution", ofGetWidth(), ofGetHeight() );
	stripes.setUniform1f( "u_time", ofGetElapsedTimef() );
	stripes.setUniform2f( "u_mouse", systemLocation.x, systemLocation.y );
	stripes.setUniform1f( "u_timer", timer );
	stripes.setUniform1f( "u_blur", flareStripeBlur );
	stripes.setUniform1f( "u_brightness", flareStripeBrightness );
	stripes.setUniform1f( "u_size", flareStripeSize );



	ofDrawRectangle( 0, 0, ofGetWidth(), ofGetHeight() );
	stripes.end();

}

//--------------------------------------------
void ofApp::bokeh()
{

	for( int i = 0; i < systems.size(); i++ ) {
		systems[i].draw();

		//  only do certain amount of particles
		for( int j = 0; j < systems[i].particleList.size(); j += 60 ) {

			//  checking life span and normalize it
			float lifespan = ofClamp( systems[i].particleList[j].lifespan / 255, 0.0, 1.0 );

			shader.begin();
			shader.setUniform2f( "u_resolution", ofGetWidth(), ofGetHeight() );
			shader.setUniform1f( "u_time", ofGetElapsedTimef() );
			shader.setUniform2f( "u_mouse", systems[i].particleList[j].pos.x, systems[i].particleList[j].pos.y );
			shader.setUniform1f( "u_particle_lifespan", lifespan );
			shader.setUniform1f( "u_aspectRatio", windowSize.x / windowSize.y );
			shader.setUniform1i( "u_sides", bokehSides );
			shader.setUniform1f( "u_size", bokehSize );
			ofDrawRectangle( 0, 0, ofGetWidth(), ofGetHeight() );
			shader.end();

		}
	}

}

//--------------------------------------------
void ofApp::flareBar()
{

	for( int i = 0; i < systems.size(); i++ ) {
		systems[i].draw();

		//  only do certain amount of particles
		for( int j = 0; j < systems[i].particleList.size(); j += 230 ) {

			//  checking life span and normalize it
			float lifespan = ofClamp( systems[i].particleList[j].lifespan / 255, 0.0, 1.0 );
			flare.begin();
			flare.setUniform2f( "u_resolution", ofGetWidth(), ofGetHeight() );
			flare.setUniform1f( "u_time", ofGetElapsedTimef() );
			flare.setUniform2f( "u_mouse", systems[i].particleList[j].pos.x, systems[i].particleList[j].pos.y );
			flare.setUniform1f( "u_particle_lifespan", lifespan );
			flare.setUniform1f( "u_aspectRatio", windowSize.x / windowSize.y );
			flare.setUniform1f( "u_range", flareBarRange );
			flare.setUniform1f( "u_thickness", flareBarThickness );
			ofDrawRectangle( 0, 0, ofGetWidth(), ofGetHeight() );
			flare.end();

		}
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed( int key )
{

}

//--------------------------------------------------------------
void ofApp::keyReleased( int key )
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved( int x, int y )
{
	ofShowCursor();
}

//--------------------------------------------------------------
void ofApp::mouseDragged( int x, int y, int button )
{

}

//--------------------------------------------------------------
void ofApp::mousePressed( int x, int y, int button )
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased( int x, int y, int button )
{
	ParticleSystem system( ofVec2f( x, y ) );
	systemLocation = ofVec2f( x, y );
	systems.push_back( system );
	timestamp = ofGetElapsedTimef();
	enableEffects = true;
}

//--------------------------------------------------------------
void ofApp::windowResized( int w, int h )
{

}

//--------------------------------------------------------------
void ofApp::gotMessage( ofMessage msg )
{

}

//--------------------------------------------------------------
void ofApp::dragEvent( ofDragInfo dragInfo )
{

}
