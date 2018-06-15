/*  ___ _  ___ _ _                                                                                                    *\
 * / __| |/ (_) | |     Your SKilL cpp Binding                                                                        * 
 * \__ \ ' <| | | |__   <<debug>>                                                                                     * 
 * |___/_|\_\_|_|____|  by: <<some developer>>                                                                        * 
\*                                                                                                                    */

#include <skill/internal/UnknownBasePool.h>
#include <skill/internal/FileParser.h>
#include "File.h"
#include "StringKeeper.h"

namespace empty {
    //! create the string pool
    static ::skill::internal::StringPool *initializeStrings(::skill::streams::FileInputStream *in) {
        auto keeper = new StringKeeper;
        ::skill::internal::StringPool *pool = new ::skill::internal::StringPool(in, keeper);
        return pool;
    }

//!create a new pool in the target type system
static ::skill::internal::AbstractStoragePool *makePool(::skill::TypeID typeID,
                                               ::skill::api::String name,
                                               ::skill::internal::AbstractStoragePool *superPool,
                                               std::set<::skill::restrictions::TypeRestriction *> *restrictions,
                                               const ::skill::internal::AbstractStringKeeper *const keeper) {

    if (nullptr == superPool)
        return new ::skill::internal::UnknownBasePool(typeID, name, restrictions);
    else
        return superPool->makeSubPool(typeID, name, restrictions);
}

    //! create a new state in the target type system
    static ::skill::api::SkillFile *makeState(::skill::streams::FileInputStream *in,
                                              ::skill::WriteMode mode,
                                              ::skill::internal::StringPool *String,
                                              ::skill::fieldTypes::AnnotationType *Annotation,
                                              std::vector<::skill::internal::AbstractStoragePool*> *types,
                                              ::skill::api::typeByName_t *typesByName,
                                              std::vector<std::unique_ptr<::skill::streams::MappedInStream>> &dataList) {

        Annotation->init();

        // create field structure
        for (auto &t : *types) {
            t->allocateData();
            if (nullptr == t->superPool) {
                ::skill::internal::AbstractStoragePool::setNextPools(t);
            }
        }

        // allocate instances
#pragma omp parallel for schedule(dynamic)
        for (size_t i = 0; i < types->size(); i++)
            types->at(i)->allocateInstances();

        ::skill::internal::triggerFieldDeserialization(types, dataList);

        return new ::empty::api::SkillFile(in, mode, String, Annotation, types, typesByName);
    }
}
::empty::api::SkillFile *::empty::api::SkillFile::open(const std::string &path,
                                                   ::skill::api::ReadMode rm,
                                                   ::skill::api::WriteMode wm) {
    return (::empty::api::SkillFile *) (
            (::skill::api::ReadMode::create == rm) ?
            ::skill::internal::newFile<
                    ::empty::initializeStrings,
                    ::empty::makePool,
                    ::empty::makeState>(path, wm) :
            ::skill::internal::parseFile<
                    ::empty::initializeStrings,
                    ::empty::makePool,
                    ::empty::makeState>(
                    std::unique_ptr<::skill::streams::FileInputStream>(
                            new ::skill::streams::FileInputStream(path)),
                    wm));
}
