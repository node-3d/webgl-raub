var WebGL=require('../../index'),
    Image = WebGL.Image,
    document = WebGL.document(),
    nodejs = true;
document.setTitle("Camera");
window = document;
requestAnimationFrame = document.requestAnimationFrame;

//Read and eval library
fs=require('fs');
eval(fs.readFileSync(__dirname+ '/lightgl.js','utf8'));
eval(fs.readFileSync(__dirname+ '/csg.min.js','utf8'));

// Set the color of all polygons in this solid
CSG.prototype.setColor = function(r, g, b) {
  this.toPolygons().map(function(polygon) {
    polygon.shared = [r, g, b];
  });
};

// Convert from CSG solid to GL.Mesh object
CSG.prototype.toMesh = function() {
  var mesh = new GL.Mesh({ normals: true, colors: true });
  var indexer = new GL.Indexer();
  this.toPolygons().map(function(polygon) {
    var indices = polygon.vertices.map(function(vertex) {
      vertex.color = polygon.shared;
      return indexer.add(vertex);
    });
    for (var i = 2; i < indices.length; i++) {
      mesh.triangles.push([indices[0], indices[i - 1], indices[i]]);
    }
  });
  mesh.vertices = indexer.unique.map(function(v) { return [v.pos.x, v.pos.y, v.pos.z]; });
  mesh.normals = indexer.unique.map(function(v) { return [v.normal.x, v.normal.y, v.normal.z]; });
  mesh.colors = indexer.unique.map(function(v) { return v.color; });
  mesh.computeWireframe();
  return mesh;
};

var angleX = 20;
var angleY = 20;
var viewers = [];

// A viewer is a WebGL canvas that lets the user view a mesh. The user can
// tumble it around by dragging the mouse.
function Viewer(csg, width, height, depth) {
  viewers.push(this);

  // Get a new WebGL canvas
  var gl = GL.create();
  this.gl = gl;
  this.mesh = csg.toMesh();

  // Set up the viewport
  gl.canvas=document.createElement('canvas', width, height); // TODO this line should not be here. setWidth/Height should reset the canvas
  gl.canvas.width = width;
  gl.canvas.height = height;
  gl.viewport(0, 0, width, height);
  gl.matrixMode(gl.PROJECTION);
  gl.loadIdentity();
  gl.perspective(45, width / height, 0.1, 100);
  gl.matrixMode(gl.MODELVIEW);

  // Set up WebGL state
  gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);
  gl.clearColor(0.93, 0.93, 0.93, 1);
  gl.enable(gl.DEPTH_TEST);
  gl.enable(gl.CULL_FACE);
  gl.polygonOffset(1, 1);

  // Black shader for wireframe
  this.blackShader = new GL.Shader('\
    void main() {\
      gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\
    }\
  ', '\
    void main() {\
      gl_FragColor = vec4(0.0, 0.0, 0.0, 0.3);\
    }\
  ');

  // Shader with diffuse and specular lighting
  this.lightingShader = new GL.Shader('\
    varying vec3 color;\
    varying vec3 normal;\
    varying vec3 light;\
    void main() {\
      const vec3 lightDir = vec3(1.0, 2.0, 3.0) / 3.741657386773941;\
      light = (gl_ModelViewMatrix * vec4(lightDir, 0.0)).xyz;\
      color = gl_Color.rgb;\
      normal = gl_NormalMatrix * gl_Normal;\
      gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\
    }\
  ', '\
    varying vec3 color;\
    varying vec3 normal;\
    varying vec3 light;\
    void main() {\
      vec3 n = normalize(normal);\
      float diffuse = max(0.0, dot(light, n));\
      float specular = pow(max(0.0, -reflect(light, n).z), 32.0) * sqrt(diffuse);\
      gl_FragColor = vec4(mix(color * (0.3 + 0.7 * diffuse), vec3(1.0), specular), 1.0);\
    }\
  ');

  gl.onmousemove = function(e) {
    if (e.dragging) {
      angleY += e.deltaX * 2;
      angleX += e.deltaY * 2;
      angleX = Math.max(-90, Math.min(90, angleX));

      viewers.map(function(viewer) {
        viewer.gl.ondraw();
      });
    }
  };

  var that = this;
  gl.ondraw = function() {
    gl.makeCurrent();

    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gl.loadIdentity();
    gl.translate(0, 0, -depth);
    gl.rotate(angleX, 1, 0, 0);
    gl.rotate(angleY, 0, 1, 0);

    gl.enable(gl.POLYGON_OFFSET_FILL);
    that.lightingShader.draw(that.mesh, gl.TRIANGLES);
    gl.disable(gl.POLYGON_OFFSET_FILL);

    gl.enable(gl.BLEND);
    that.blackShader.draw(that.mesh, gl.LINES);
    gl.disable(gl.BLEND);
  };

  gl.animate();
}

var nextID = 0;
function addViewer(viewer) {
   //document.getElementById(nextID++).appendChild(viewer.gl.canvas);
}

// Test simple cases
/*var a = CSG.cube({ center: [-0.25, -0.25, -0.25] });
var b = CSG.sphere({ radius: 1.3, center: [0.25, 0.25, 0.25] });
a.setColor(1, 0, 0);
b.setColor(0, 0, 1);
var operations = [
  a,
  b,
  a.union(b),
  a.subtract(b),
  a.intersect(b)
];
for (var i = 0; i < operations.length; i++) {
  addViewer(new Viewer(operations[i], 200, 200, 6));
}*/

// Generate example from wikipedia
var a = CSG.cube();
var b = CSG.sphere({ radius: 1.35, stacks: 12 });
var c = CSG.cylinder({ radius: 0.7, start: [-1, 0, 0], end: [1, 0, 0] });
var d = CSG.cylinder({ radius: 0.7, start: [0, -1, 0], end: [0, 1, 0] });
var e = CSG.cylinder({ radius: 0.7, start: [0, 0, -1], end: [0, 0, 1] });
a.setColor(1, 0, 0);
b.setColor(0, 0, 1);
c.setColor(0, 1, 0);
d.setColor(0, 1, 0);
e.setColor(0, 1, 0);
/*var operations = [
  a,
  b,
  c,
  d,
  e,
  a.intersect(b).subtract(c.union(d).union(e))
];
for (var i = 0; i < operations.length; i++) {
  var size = i + 1 == operations.length ? 400 : 150;
  addViewer(new Viewer(operations[i], size, size, 5));
}*/

addViewer(new Viewer(a.intersect(b).subtract(c.union(d).union(e)), 400, 400, 5));
