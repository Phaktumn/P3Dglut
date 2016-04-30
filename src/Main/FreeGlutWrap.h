#ifndef  __FREEGLUT_WRAP_H__
#define  __FREEGLUT_WRAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef FREEGLUT_GLES
#   include <EGL/egl.h>
#   include <GLES/gl.h>
#   include <GLES2/gl2.h>
#   include <Vars/vec3f.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <Vars/vec3f.h>
#endif

	using namespace vec;

	inline void APIENTRY _gluLookAt(const Vector3& _Position, const Vector3& _lookAt, const Vector3& _upVec) {
		gluLookAt(_Position.x, _Position.y, _Position.z, _lookAt.x, _lookAt.y, _lookAt.z, _upVec.x, _upVec.y, _upVec.z);
	} 

	inline void APIENTRY _glRotatef(double angle, const Vector3& _RotAxis){
		glRotatef(angle, _RotAxis.x, _RotAxis.y, _RotAxis.z);
	}

	inline void APIENTRY _glTranslate(const Vector3& _Tranlate_Vec){
		glTranslatef(_Tranlate_Vec.x, _Tranlate_Vec.y, _Tranlate_Vec.z);
	}

	inline void APIENTRY _Scale(const Vector3& _scale_Vec){
		glScalef(_scale_Vec.x, _scale_Vec.y, _scale_Vec.z);
	}

	inline void APIENTRY _Vertex3(const Vector3& _Vector){
		glVertex3f(_Vector.x, _Vector.y, _Vector.z);
	}

	inline void APIENTRY _BindTexture(const GLuint _Texture_ID){
		glBindTexture(GL_TEXTURE_2D, _Texture_ID);
	}

	//************************************
	// Qualifier: Use X as X and Y as Z in your Vector3
	// Parameter: const Vector3 & _vectorXz
	//************************************
	inline void APIENTRY _RasterPos2(const Vector3& _vectorXz){
		glRasterPos2f(_vectorXz.x, _vectorXz.z);
	}

#ifdef __cplusplus
}
#endif

#endif /* __FREEGLUT_WRAP_H__ */