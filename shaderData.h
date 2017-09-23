#ifdef SHADER_DATA
#undef SHADER_DATA
const char* rectVert = "#version 430\n"
					   "layout(location = 0) in vec2 position;\n"
					   "layout(location = 0) uniform mat4 mvp;\n"
					   "void main()\n"
					   "{\n"
					   "	gl_Position = mvp * vec4(position, 0.0f, 1.0f);\n"
					   "}\n";
const char* rectFrag = "#version 430\n"
					   "layout(location = 0) out vec4 outColor;\n"
					   "layout(location = 1) uniform vec4 color;\n"
					   "void main()\n"
					   "{\n"
					   "	outColor = color;\n"
					   "}\n";
const char* circleVert = "#version 430\n"
						 "layout(location = 0) in vec2 position;\n"
						 "layout(location = 0) out vec2 fragPos;\n"
						 "layout(location = 0) uniform mat4 mvp;\n"
						 "void main()\n"
						 "{\n"
						 "	gl_Position = mvp * vec4(position, 0.0f, 1.0f);\n"
						 "	fragPos = position;\n"
						 "}\n";
const char* circleFrag = "#version 430\n"
						 "layout(location = 0) in vec2 fragPos;\n"
						 "layout(location = 0) out vec4 outColor;\n"
						 "layout(location = 1) uniform vec4 color;\n"
						 "void main()\n"
						 "{\n"
						 "	if(dot(fragPos, fragPos) > 0.25f) discard;\n"
						 "	outColor = color;\n"
						 "}\n";
#endif