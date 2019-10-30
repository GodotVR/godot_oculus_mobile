/**
* Created by Fredia Huya-Kouadio.
*/

#ifndef JNI_COMMON_H
#define JNI_COMMON_H

/** Auxiliary macros */
#define __JNI_METHOD_BUILD(package, class_name, method) \
    Java_ ## package ## _ ## class_name ## _ ## method
#define __JNI_METHOD_EVAL(package, class_name, method) \
    __JNI_METHOD_BUILD(package, class_name, method)

/**
 * Expands the JNI signature for a JNI method.
 *
 * Requires to redefine the macros JNI_PACKAGE_NAME and JNI_CLASS_NAME.
 * Not doing so will raise preprocessor errors during build.
 *
 * JNI_PACKAGE_NAME must be the JNI representation Java class package name.
 * JNI_CLASS_NAME must be the JNI representation of the Java class name.
 *
 * For example, for the class com.example.package.SomeClass:
 * JNI_PACKAGE_NAME: com_example_package
 * JNI_CLASS_NAME: SomeClass
 *
 * Note that underscores in Java package and class names are replaced with "_1"
 * in their JNI representations.
 */
#define JNI_METHOD(method) \
    __JNI_METHOD_EVAL(JNI_PACKAGE_NAME, JNI_CLASS_NAME, method)

/**
 * Expands a Java class name using slashes as package separators into its
 * JNI type string representation.
 *
 * For example, to get the JNI type representation of a Java String:
 * JAVA_TYPE("java/lang/String")
 */
#define JAVA_TYPE(class_name) "L" class_name ";"

/**
 * Default definitions for the macros required in JNI_METHOD.
 * Used to raise build errors if JNI_METHOD is used without redefining them.
 */
#define JNI_CLASS_NAME "Error: JNI_CLASS_NAME not redefined"
#define JNI_PACKAGE_NAME "Error: JNI_PACKAGE_NAME not redefined"

ovrmobile::OvrMobileSession* get_session();

#endif // JNI_COMMON_H
