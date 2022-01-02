#please use 'make clean' to clean the directory of intermediate build files and the executable
#simply typing 'make' will compile all source code files to object files .o, and then link all
#object files into an executable
#we are using a lot of makefile macros

#changing platform dependant stuff, do not change this
# Linux (default)
LDFLAGS = -lGL -lGLU -lglut
CXXFLAGS=-g -Wall -std=c++11
CXX=g++
EXEEXT=
RM=rm


# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
	EXEEXT=.exe #on windows applications must have .exe extension
	RM=rm #del command for windows powershell
    LDFLAGS = -lglew32 -lfreeglut -lglu32 -lopengl32
else
# OS X
	OS := $(shell uname)
	ifeq ($(OS), Darwin)
	        LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT
	endif
endif


# Directories
DIR_LOADERS=Loaders
DIR_LIB=Libraries
DIR_MODEL=AnimatedModel
DIR_ANIM=Animation
DIR_XML=ColladaParser/XML
DIR_DATA=ColladaParser/DataStructures
DIR_LOAD=ColladaParser/Loader
DIR_SHADER=Engine/Shaders
DIR_UNI=Engine/Uniform
DIR_TEX=Engine/Textures

#objects
#ColladaParser
LOADERS_OBJ=$(DIR_LOADERS)/AnimatedModelLoader.o $(DIR_LOADERS)/AnimationLoader.o

LOAD_OBJ=$(DIR_LOAD)/ColladaLoader.o $(DIR_LOAD)/GeometryLoader.o $(DIR_LOAD)/SkeletonLoader.o $(DIR_LOAD)/SkinLoader.o $(DIR_LOAD)/ColladaAnimationLoader.o
XML_OBJ=$(DIR_XML)/XmlParser.o $(DIR_XML)/XmlNode.o

DATA1_OBJ=$(DIR_DATA)/AnimatedModelData.o $(DIR_DATA)/JointData.o $(DIR_DATA)/JointTransformData.o 
DATA2_OBJ=$(DIR_DATA)/AnimationData.o $(DIR_DATA)/KeyFrameData.o $(DIR_DATA)/MeshData.o $(DIR_DATA)/SkinningData.o
DATA3_OBJ=$(DIR_DATA)/SkeletonData.o $(DIR_DATA)/VertexSkinData.o $(DIR_DATA)/Vertex.o 
DATA_OBJ=$(DATA1_OBJ) $(DATA2_OBJ) $(DATA3_OBJ) 

PARSER_OBJ=$(XML_OBJ) $(DATA_OBJ) $(LOAD_OBJ)

#Animated Model + Libraries
MOD_OBJ=$(DIR_MODEL)/AnimatedModel.o $(DIR_MODEL)/Joint.o
ANI_OBJ=$(DIR_ANIM)/Animation.o $(DIR_ANIM)/Animator.o $(DIR_ANIM)/JointTransform.o $(DIR_ANIM)/KeyFrame.o
LIB_OBJ=$(DIR_LIB)/stringfn.o $(DIR_LIB)/Vao.o $(DIR_LIB)/Vbo.o

#Shaders, Uniforms
SHADER_OBJ = $(DIR_SHADER)/ShaderProgram.o $(DIR_SHADER)/EntityShader.o
UNI_OBJ=$(DIR_UNI)/Uniform.o $(DIR_UNI)/UniformBoolean.o $(DIR_UNI)/UniformFloat.o $(DIR_UNI)/UniformMat4Array.o $(DIR_UNI)/UniformMatrix.o $(DIR_UNI)/UniformSampler.o $(DIR_UNI)/UniformVec2.o $(DIR_UNI)/UniformVec3.o $(DIR_UNI)/UniformVec4.o
TEX_OBJ=$(DIR_TEX)/Texture.o $(DIR_TEX)/TextureSettings.o $(DIR_TEX)/TextureData.o $(DIR_TEX)/TextureUtils.o

#collated objects
OBJ=$(LOADERS_OBJ) $(PARSER_OBJ) $(MOD_OBJ) $(ANI_OBJ) $(LIB_OBJ) $(SHADER_OBJ) $(UNI_OBJ) $(TEX_OBJ)

#change the 't1' name to the name you want to call your application
PROGRAM_NAME=main

#run target to compile and build, and then launch the executable
run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME)$(EXEEXT)

#when adding additional source files, such as boilerplateClass.cpp
#or yourFile.cpp, add the filename with an object extension below
#ie. boilerplateClass.o and yourFile.o
#make will automatically know that the objectfile needs to be compiled
#form a cpp source file and find it itself :)
$(PROGRAM_NAME): main.o Scene.o SceneLoader.o $(OBJ) 
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)


clean:
	$(RM) $(PROGRAM_NAME) $(EXEEXT) *.o $(DIR_LIB)/*.o $(DIR_MODEL)/*.o $(DIR_ANIM)/*.o $(DIR_XML)/*.o $(DIR_DATA)/*.o $(DIR_LOAD)/*.o $(DIR_LOADERS)/*.o $(DIR_SHADER)/*.o $(DIR_UNI)/*.o $(DIR_TEX)/*.o

	
