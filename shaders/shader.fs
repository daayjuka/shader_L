#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec3 ourPosition;


uniform float xColorSet, yColorSet, zColorSet;
  
void main()
{
    FragColor = vec4(ourColor.x - xColorSet, ourColor.y - yColorSet, ourColor.z - zColorSet, 1.0);
}
