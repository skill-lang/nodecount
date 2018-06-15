/*  ___ _  ___ _ _                                                                                                    *\
 * / __| |/ (_) | |     Your SKilL cpp Binding                                                                        * 
 * \__ \ ' <| | | |__   <<debug>>                                                                                     * 
 * |___/_|\_\_|_|____|  by: <<some developer>>                                                                        * 
\*                                                                                                                    */
#ifndef SKILL_CPP_GENERATED_EMPTY_FILE
#define SKILL_CPP_GENERATED_EMPTY_FILE

#include <skill/fieldTypes/AnnotationType.h>
#include <skill/api/SkillFile.h>

namespace empty {
    namespace api {
        /**
         * A skill file that corresponds to your specification. Have fun!
         *
         * @author Timm Felden
         */
        struct SkillFile : public ::skill::api::SkillFile {

/*(
  _path : Path,
  _mode : WriteMode,
  _String : StringPool,
  _annotationType : fieldTypes.AnnotationType,
  _types : ArrayBuffer[StoragePool[_ <: SkillObject, _ <: SkillObject]],
  _typesByName : HashMap[String, StoragePool[_ <: SkillObject, _ <: SkillObject]])
    extends SkillState(_path, _mode, _String, _annotationType, _types, _typesByName) {*/


            /**
             * !internal use only
             */
            SkillFile(skill::streams::FileInputStream *in, const skill::api::WriteMode &mode,
                      skill::internal::StringPool *stringPool, skill::fieldTypes::AnnotationType *annotation,
                      std::vector<skill::internal::AbstractStoragePool*> *types,
                      skill::api::typeByName_t *typesByName)
                    : ::skill::api::SkillFile(in, mode, stringPool, annotation, types, typesByName) {
                ensureFields();
            }

            /**
             * Reads a binary SKilL file and turns it into a SKilL state.
             */
            static SkillFile *open(const std::string &path,
                                   ::skill::api::ReadMode rm = ::skill::api::ReadMode::read,
                                   ::skill::api::WriteMode wm = ::skill::api::WriteMode::write);

            static SkillFile *create(const std::string &path,
                                     ::skill::api::WriteMode wm = ::skill::api::WriteMode::write) {
                return open(path, ::skill::api::ReadMode::create, wm);
            }

            static SkillFile *read(const std::string &path,
                                     ::skill::api::WriteMode wm = ::skill::api::WriteMode::write) {
                return open(path, ::skill::api::ReadMode::read, wm);
            }
        };
}}

#endif