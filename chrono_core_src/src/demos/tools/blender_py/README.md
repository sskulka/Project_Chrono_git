Blender_py & chrono usage
=============================================

These scripts allow to use blender to render the POVRAY output of a chrono simulation.

## Tool description
#### Structure
This tools is composed of 3 Python scripts
1. reader.py : this script interprets the POVRAY output generated by Chrono simulation and outputs a list of lists of data
2. blend_pproc_render.py : this is the main script, that based on the information provided by _reader.py_ builds a scene and creates images 
2. blender_postprocess_launcher.py: this is the sctipts that has to be launched and, ideally, the only one the user should edit. After setting the renderin options, it calls the bl_render functio from blend_pproc_render.py

#### Requirements

This tool only requires blender-py (bpy). If you already have Blender, use its Pytohn interpreter.
If not, you can install blender-py with  [pip](https://pypi.org/project/bpy/) .
In addition, numpy is required.

## Usage
#### Setup
Set the options in _blender_postprocess_launcher.py_ :
1. meshes_prefixes : list of strings. Paths to meshes folders.
2. out_dir : where to output the generated images.
2. datadir : where the .dat files generated by chrono are
3. res : images resolution: 'LOW', 'MID', 'HIGH' Images in HIGH defnition take a while to generate.
4. camera_mode : 'Follow' 'Fixed' 'Lookat'. 
5. use_sky : if True, uses a Blender default sky
6. camera_pos : position of the camera. Not used in 'Follow' mode.
7. targ_bodyid / targ_shapetypeid / targ_name / in 'Follow' and 'Lookat' mode the target os found using these information. The tatget is a shape on a body. targ_bodyid is the ID of the body, targ_shapetypeid is the type of shape (5 for meshes), targ_name is the name if the target mesh (used only if targ_shapetypeid=5)
8. camera_dist : only used in 'Follow' mode. The distance, in the body local frame, of the camera from the target.
8. light_loc / light_energy location and intensity of the light energy.

#### Launch
Once the variables in _blender_postprocess_launcher.py_ are set, just launch it remembering to use the Pytohn interpreter that has blender-py installed.

## Limitations and future features
#### Current Limitiations 
1. The code does not leverage multiprocessing (HD render are time consuming)
2. No default terrain
3. NO support for granular and FSI
4. Textures cannot be added to meshes

#### Coming soon
(1) will be addressed very soon, and (2) and (3) will follow shortly.

