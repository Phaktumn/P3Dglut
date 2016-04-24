#ifndef  __FREEGLUT_WRAP_H__
#define  __FREEGLUT_WRAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef FREEGLUT_GLES
#   include <EGL/egl.h>
#   include <GLES/gl.h>
#   include <GLES2/gl2.h>
#    include <Vars/vec3f.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <Vars/vec3f.h>
#endif

	using namespace vec;

	inline
	void _glRotatef(double angle, const Vector3& _RotAxis){
		glRotatef(angle, _RotAxis.x, _RotAxis.y, _RotAxis.z);
	}

	inline 
	void _glTranslate(const Vector3& _Tranlate_Vec){
		glTranslatef(_Tranlate_Vec.x, _Tranlate_Vec.y, _Tranlate_Vec.z);
	}

	inline
	void _Scale(const Vector3& _scale_Vec){
		glScalef(_scale_Vec.x, _scale_Vec.y, _scale_Vec.z);
	}

	inline
	void _Vertex3(const Vector3& _Vector){
		glVertex3f(_Vector.x, _Vector.y, _Vector.z);
	}

#ifdef __cplusplus
}
#endif

#endif /* __FREEGLUT_WRAP_H__ */