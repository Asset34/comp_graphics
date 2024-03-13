
--boundary_.oOo._q1tDrBFE8n0HWqG1Y2JeXdswGMZcZIu4
Content-Length: 35988
Content-Type: application/octet-stream
X-File-MD5: fcae8a24de010fc89f313138d59d42ad
X-File-Mtime: 1708970791
X-File-Path: /Home/1. Projects/Comp_graphics/LR1/include/glm/gtc/packing.hpp

/// @ref gtc_packing
/// @file glm/gtc/packing.hpp
///
/// @see core (dependence)
///
/// @defgroup gtc_packing GLM_GTC_packing
/// @ingroup gtc
///
/// Include <glm/gtc/packing.hpp> to use the features of this extension.
///
/// This extension provides a set of function to convert vertors to packed
/// formats.

#pragma once

// Dependency:
#include "type_precision.hpp"
#include "../ext/vector_packing.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_GTC_packing extension included")
#endif

namespace glm
{
	/// @addtogroup gtc_packing
	/// @{

	/// First, converts the normalized floating-point value v into a 8-bit integer value.
	/// Then, the results are packed into the returned 8-bit unsigned integer.
	///
	/// The conversion for component c of v to fixed point is done as follows:
	/// packUnorm1x8:	round(clamp(c, 0, +1) * 255.0)
	///
	/// @see gtc_packing
	/// @see uint16 packUnorm2x8(vec2 const& v)
	/// @see uint32 packUnorm4x8(vec4 const& v)
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packUnorm4x8.xml">GLSL packUnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL uint8 packUnorm1x8(float v);

	/// Convert a single 8-bit integer to a normalized floating-point value.
	///
	/// The conversion for unpacked fixed-point value f to floating point is done as follows:
	/// unpackUnorm4x8: f / 255.0
	///
	/// @see gtc_packing
	/// @see vec2 unpackUnorm2x8(uint16 p)
	/// @see vec4 unpackUnorm4x8(uint32 p)
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackUnorm4x8.xml">GLSL unpackUnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL float unpackUnorm1x8(uint8 p);

	/// First, converts each component of the normalized floating-point value v into 8-bit integer values.
	/// Then, the results are packed into the returned 16-bit unsigned integer.
	///
	/// The conversion for component c of v to fixed point is done as follows:
	/// packUnorm2x8:	round(clamp(c, 0, +1) * 255.0)
	///
	/// The first component of the vector will be written to the least significant bits of the output;
	/// the last component will be written to the most significant bits.
	///
	/// @see gtc_packing
	/// @see uint8 packUnorm1x8(float const& v)
	/// @see uint32 packUnorm4x8(vec4 const& v)
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packUnorm4x8.xml">GLSL packUnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL uint16 packUnorm2x8(vec2 const& v);

	/// First, unpacks a single 16-bit unsigned integer p into a pair of 8-bit unsigned integers.
	/// Then, each component is converted to a normalized floating-point value to generate the returned two-component vector.
	///
	/// The conversion for unpacked fixed-point value f to floating point is done as follows:
	/// unpackUnorm4x8: f / 255.0
	///
	/// The first component of the returned vector will be extracted from the least significant bits of the input;
	/// the last component will be extracted from the most significant bits.
	///
	/// @see gtc_packing
	/// @see float unpackUnorm1x8(uint8 v)
	/// @see vec4 unpackUnorm4x8(uint32 p)
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackUnorm4x8.xml">GLSL unpackUnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL vec2 unpackUnorm2x8(uint16 p);

	/// First, converts the normalized floating-point value v into 8-bit integer value.
	/// Then, the results are packed into the returned 8-bit unsigned integer.
	///
	/// The conversion to fixed point is done as follows:
	/// packSnorm1x8:	round(clamp(s, -1, +1) * 127.0)
	///
	/// @see gtc_packing
	/// @see uint16 packSnorm2x8(vec2 const& v)
	/// @see uint32 packSnorm4x8(vec4 const& v)
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packSnorm4x8.xml">GLSL packSnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL uint8 packSnorm1x8(float s);

	/// First, unpacks a single 8-bit unsigned integer p into a single 8-bit signed integers.
	/// Then, the value is converted to a normalized floating-point value to generate the returned scalar.
	///
	/// The conversion for unpacked fixed-point value f to floating point is done as follows:
	/// unpackSnorm1x8: clamp(f / 127.0, -1, +1)
	///
	/// @see gtc_packing
	/// @see vec2 unpackSnorm2x8(uint16 p)
	/// @see vec4 unpackSnorm4x8(uint32 p)
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackSnorm4x8.xml">GLSL unpackSnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL float unpackSnorm1x8(uint8 p);

	/// First, converts each component of the normalized floating-point value v into 8-bit integer values.
	/// Then, the results are packed into the returned 16-bit unsigned integer.
	///
	/// The conversion for component c of v to fixed point is done as follows:
	/// packSnorm2x8:	round(clamp(c, -1, +1) * 127.0)
	///
	/// The first component of the vector will be written to the least significant bits of the output;
	/// the last component will be written to the most significant bits.
	///
	/// @see gtc_packing
	/// @see uint8 packSnorm1x8(float const& v)
	/// @see uint32 packSnorm4x8(vec4 const& v)
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packSnorm4x8.xml">GLSL packSnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL uint16 packSnorm2x8(vec2 const& v);

	/// First, unpacks a single 16-bit unsigned integer p into a pair of 8-bit signed integers.
	/// Then, each component is converted to a normalized floating-point value to generate the returned two-component vector.
	///
	/// The conversion for unpacked fixed-point value f to floating point is done as follows:
	/// unpackSnorm2x8: clamp(f / 127.0, -1, +1)
	///
	/// The first component of the returned vector will be extracted from the least significant bits of the input;
	/// the last component will be extracted from the most significant bits.
	///
	/// @see gtc_packing
	/// @see float unpackSnorm1x8(uint8 p)
	/// @see vec4 unpackSnorm4x8(uint32 p)
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackSnorm4x8.xml">GLSL unpackSnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL vec2 unpackSnorm2x8(uint16 p);

	/// First, converts the normalized floating-point value v into a 16-bit integer value.
	/// Then, the results are packed into the returned 16-bit unsigned integer.
	///
	/// The conversion for component c of v to fixed point is done as follows:
	/// packUnorm1x16:	round(clamp(c, 0, +1) * 65535.0)
	///
	/// @see gtc_packing
	/// @see uint16 packSnorm1x16(float const& v)
	/// @see uint64 packSnorm4x16(vec4 const& v)
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packUnorm4x8.xml">GLSL packUnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack an