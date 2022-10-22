#shader vertex
#version 110

attribute vec4 position;

void main(){
   gl_Position = position;
}

#shader fragment
#version 110

void main(){
   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}