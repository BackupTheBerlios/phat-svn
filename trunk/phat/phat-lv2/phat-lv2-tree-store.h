/* Generated by GOB (v2.0.12)   (do not edit directly) */

#include <glib.h>
#include <glib-object.h>


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdk.h>
#include <gtk/gtk.h>

#include <slv2/slv2.h>

#ifndef __PHAT_LV2_TREE_STORE_H__
#define __PHAT_LV2_TREE_STORE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 * Type checking and casting macros
 */
#define PHAT_TYPE_LV2_TREE_STORE	(phat_lv2_tree_store_get_type())
#define PHAT_LV2_TREE_STORE(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), phat_lv2_tree_store_get_type(), PhatLV2TreeStore)
#define PHAT_LV2_TREE_STORE_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), phat_lv2_tree_store_get_type(), PhatLV2TreeStore const)
#define PHAT_LV2_TREE_STORE_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), phat_lv2_tree_store_get_type(), PhatLV2TreeStoreClass)
#define PHAT_IS_LV2_TREE_STORE(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), phat_lv2_tree_store_get_type ())

#define PHAT_LV2_TREE_STORE_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), phat_lv2_tree_store_get_type(), PhatLV2TreeStoreClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_PHAT_LV2_TREE_STORE__
#define __TYPEDEF_PHAT_LV2_TREE_STORE__
typedef struct _PhatLV2TreeStore PhatLV2TreeStore;
#endif
struct _PhatLV2TreeStore {
	GtkTreeStore __parent__;
};

/*
 * Class definition
 */
typedef struct _PhatLV2TreeStoreClass PhatLV2TreeStoreClass;
struct _PhatLV2TreeStoreClass {
	GtkTreeStoreClass __parent__;
};


/*
 * Public methods
 */
GType	phat_lv2_tree_store_get_type	(void);
GtkTreeModel * 	phat_lv2_tree_store_new	(void);
gboolean 	phat_lv2_tree_store_lookup	(PhatLV2TreeStore * self,
					char * path,
					GtkTreeIter * iter,
					gboolean create);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
