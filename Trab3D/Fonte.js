
/**Fonte**/

/*base*/
function def_cube(){

  var points = [
                  new THREE.Vector3( 1, 0, 1),
                  new THREE.Vector3( 1, 0,-1),
                  new THREE.Vector3(-1, 0,-1),
                  new THREE.Vector3(-1, 0, 1),
                  
                  new THREE.Vector3( 1, 1, 1),
                  new THREE.Vector3( 1, 1,-1),
                  new THREE.Vector3(-1, 1,-1),
                  new THREE.Vector3(-1, 1, 1)
                 ];
                 
    var faces = [
                 //Baixo
                 new THREE.Face3( 0, 1, 2),
                 new THREE.Face3( 0, 2, 3),
                 
                 //Cima
                 new THREE.Face3( 4, 5, 6),
                 new THREE.Face3( 4, 6, 7),
                 
                 //Esquerda
                 new THREE.Face3( 0, 1, 4),
                 new THREE.Face3( 4, 1, 5),
                 
                 //Direita
                 new THREE.Face3( 3, 2, 7),
                 new THREE.Face3( 7, 2, 6),
                 
                 //Frente
                 new THREE.Face3( 1, 2, 5),
                 new THREE.Face3( 5, 2, 6),
                 
                 //Atras
                 new THREE.Face3( 0, 3, 7),
                 new THREE.Face3( 7, 0, 4),
                 
                ];
                
  var geo = new THREE.Geometry();
  geo.vertices = points;
  geo.faces = faces;
  geo.computeFaceNormals(); // get the right "outside"
  geo.computeBoundingSphere(); // to help the rendering system
  
  var mesh =  new THREE.MeshLambertMaterial( {color: "crimson" } );
  mesh.side = THREE.DoubleSide;
  var obj = new THREE.Mesh(geo, mesh);
  obj.position.set(0,0,0);
  
  return obj;

}

function base_1(){

	var base = new THREE.Mesh();

  var base1 = def_cube();
  var base2 = def_cube();
  var base3 = def_cube();

  base1.scale.set(2,1,2);
  
  base2.scale.set(2,0.5,2);
  base2.position.set(0,0,-3);

  base3.scale.set(1.3,0.5,1.3);
  base3.position.set(0,0.5,-3);

  base.add(base1);
  base.add(base2);
  base.add(base3);
  return base;

}

function base_2(){

  var base = new THREE.Mesh();

  var base1 = def_cube();
  var base2 = def_cube();
  var base3 = def_cube();

  //base1
  base1.scale.set(1.5,0.4,1.5);

  //base2
  base2.scale.set(1.3,0.2,1.3);
  base2.position.set(0,0.4,0);

  //base3
  base3.scale.set(1,0.4,1);
  base3.position.set(0,0,-3);

  base.add(base1);
  base.add(base2);
  base.add(base3);
  return base;

}


/*fonte*/
function fonte(){

  var fonte = new THREE.Mesh();

  var base1 = base_1();
  var base2 = base_2();
  
  /*
  var n_mesh = new THREE.MeshLambertMaterial( {color: "steelblue"});

  base2.material = n_mesh;
  */

  base2.position.set(0,2,0);

  fonte.add(base1);
  fonte.add(base2);
	return fonte;

}


/**main**/
function init(mesh) {  
  //
  //  Document
  //
  renderer = new THREE.WebGLRenderer({ alpha: true });
  renderer.setClearColor("khaki")
  renderer.setSize(512,512);
  document.body.appendChild(renderer.domElement);
  //
  //  Scene (World, Model)
  //
  scene = new THREE.Scene();
  //
  //  Camera (and TrackballControls)
  //
  camera = new THREE.PerspectiveCamera(
    35,       // abertura
    512/512,  // proporção largura/altura
    0.1,      // corte perto
    10000     // corte longe
    );
  camera.position.set( -2.5, 0, 20 );
  camera.lookAt( scene.position );
  controls = new THREE.TrackballControls(camera);
 
  var ambient_light = new THREE.AmbientLight(0x7F7F7F);
  scene.add( ambient_light );

  var point_light_1 = new THREE.PointLight(0x3F3F3F);
  point_light_1.position.set(5, 0, 0);
  scene.add( point_light_1 );

  var point_light_2 = new THREE.PointLight(0x3F3F3F);
  point_light_2.position.set(-5, 0, 0);
  scene.add( point_light_2 );

  scene.add( mesh );

  return {
    camera: camera,
    scene: scene,
    renderer: renderer,
    controls: controls
  }
}


function animate(step) {
  requestAnimationFrame( function() { animate(step); });
  step.controls.update();
  step.renderer.render( step.scene, step.camera);
}


function main() {
  var step = init(fonte());
  animate(step);
}

