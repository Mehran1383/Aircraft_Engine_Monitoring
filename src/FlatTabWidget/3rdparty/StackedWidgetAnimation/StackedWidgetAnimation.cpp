/*
 * Copyright (C) 2015  Dimka Novikov, to@dimkanovikov.pro
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * Full license: https://github.com/dimkanovikov/WidgetAnimationFramework/blob/master/LICENSE
 */



#include "StackedWidgetAnimation.h"
#include "StackedWidgetAnimationPrivate.h"

#include "StackedWidgetSlide/StackedWidgetSlideAnimator.h"
#include "StackedWidgetSlideOver/StackedWidgetSlideOverAnimator.h"
#include "StackedWidgetFadeIn/StackedWidgetFadeInAnimator.h"

using WAF::StackedWidgetAnimation;
using WAF::StackedWidgetAnimationPrivate;
using WAF::AbstractAnimator;
using WAF::StackedWidgetSlideAnimator;
using WAF::StackedWidgetSlideOverAnimator;
using WAF::StackedWidgetFadeInAnimator;


void StackedWidgetAnimation::slide(QStackedWidget* _container, QWidget* _widget, WAF::AnimationDirection _direction)
{
    const StackedWidgetAnimationPrivate::AnimatorType animatorType = StackedWidgetAnimationPrivate::Slide;
    AbstractAnimator* animator = nullptr;
    if (pimpl()->hasAnimator(_widget, animatorType)) {
        animator = pimpl()->animator(_widget, animatorType);
        if (auto slideAnimator = qobject_cast<StackedWidgetSlideAnimator*>(animator)) {
            slideAnimator->setAnimationDirection(_direction);
        }
    } else {
        auto slideAnimator = new StackedWidgetSlideAnimator(_container, _widget);
        slideAnimator->setAnimationDirection(_direction);
        animator = slideAnimator;

        pimpl()->saveAnimator(_widget, animator, animatorType);
    }

    animator->animateForward();
}

void StackedWidgetAnimation::slideOverIn(QStackedWidget* _container, QWidget* _widget, WAF::AnimationDirection _direction)
{
    const bool IN = true;
    slideOver(_container, _widget, _direction, IN);
}

void StackedWidgetAnimation::slideOverOut(QStackedWidget* _container, QWidget* _widget, WAF::AnimationDirection _direction)
{
    const bool OUT = false;
    slideOver(_container, _widget, _direction, OUT);
}

void StackedWidgetAnimation::slideOver(QStackedWidget* _container, QWidget* _widget, WAF::AnimationDirection _direction, bool _in)
{
    const StackedWidgetAnimationPrivate::AnimatorType animatorType = StackedWidgetAnimationPrivate::SlideOver;
    AbstractAnimator* animator = nullptr;
    if (pimpl()->hasAnimator(_widget, animatorType)) {
        animator = pimpl()->animator(_widget, animatorType);
        if (auto slideOverAnimator = qobject_cast<StackedWidgetSlideOverAnimator*>(animator)) {
            if (_in) {
                slideOverAnimator->updateCoveredWidget();
            }
            slideOverAnimator->setAnimationDirection(_direction);
        }
    } else {
        auto slideOverAnimator = new StackedWidgetSlideOverAnimator(_container, _widget);
        slideOverAnimator->setAnimationDirection(_direction);
        animator = slideOverAnimator;

        pimpl()->saveAnimator(_widget, animator, animatorType);
    }

    if (_in) {
        animator->animateForward();
    } else {
        animator->animateBackward();
    }
}

AbstractAnimator* StackedWidgetAnimation::fadeIn(QStackedWidget* _container, QWidget* _widget)
{
    const StackedWidgetAnimationPrivate::AnimatorType animatorType = StackedWidgetAnimationPrivate::FadeIn;
    AbstractAnimator* animator = nullptr;
    if (pimpl()->hasAnimator(_widget, animatorType)) {
        animator = pimpl()->animator(_widget, animatorType);
    } else {
        auto fadeInAnimator = new StackedWidgetFadeInAnimator(_container, _widget);
        animator = fadeInAnimator;
        pimpl()->saveAnimator(_widget, animator, animatorType);
    }

    animator->animateForward();

    return animator;
}

StackedWidgetAnimationPrivate* StackedWidgetAnimation::m_pimpl = nullptr;

StackedWidgetAnimationPrivate* StackedWidgetAnimation::pimpl()
{
    if (m_pimpl == nullptr) {
        m_pimpl = new StackedWidgetAnimationPrivate;
    }

    return m_pimpl;
}
