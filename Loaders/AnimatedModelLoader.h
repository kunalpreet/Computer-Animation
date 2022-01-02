#ifndef ANIMATED_MODEL_LOADER_H 
#define ANIMATED_MODEL_LOADER_H 

#include <fstream>
#include "../AnimatedModel/AnimatedModel.h"
#include "../AnimatedModel/Joint.h"
#include "../Libraries/Eigen/Dense"
#include "../ColladaParser/DataStructures/JointData.h"
#include "../ColladaParser/DataStructures/MeshData.h"
#include "../Engine/Textures/Texture.h"

class AnimatedModelLoader {
public:
	/**
	 * Creates an AnimatedEntity from the data in an entity file. It loads up
	 * the collada model data, stores the extracted data in a VAO, sets up the
	 * joint heirarchy, and loads up the entity's texture.
	 * 
	 * @param entityFile
	 *            - the file containing the data for the entity.
	 * @return The animated entity (no animation applied though)
	 */
	static AnimatedModel loadEntity(std::ifstream& modelFile, std::ifstream& textureFile);

private:

	/**
	 * Constructs the joint-hierarchy skeleton from the data extracted from the
	 * collada file.
	 * 
	 * @param data
	 *            - the joints data from the collada file for the head joint.
	 * @return The created joint, with all its descendants added.
	 */
	static Joint createJoints(JointData data);

	// passing parenttransform to child joints for calculations
	static Joint createJoints(JointData data, Eigen::Matrix4f parentBind);

	/**
	 * Stores the mesh data into a given VAO.
	 * 
	 * @param data
	 *            - all the data about the mesh that needs to be stored in the
	 *            VAO.
	 * @return The VAO containing all the mesh data for the model.
	 */
	static void loadVAO(Vao& vao, MeshData data);
};


#endif