//
//  AKImageEffect.h
//  AmazeKit
//
//  Created by Jeffrey Kelley on 6/11/12.
//  Copyright (c) 2012 Detroit Labs. All rights reserved.
//


// KVO Constants
extern NSString * const AKImageEffectDirtyKeyPath;


@interface AKImageEffect : NSObject

// Appearance Properties
@property (readonly) CGFloat    	alpha;
@property (readonly) CGBlendMode	blendMode;

// For a mutable image effect, set dirty to YES to force it to rebuild the hash on next use.
@property (getter = isDirty) BOOL	dirty;

// Image Effects are immutable by default, so use the designated initializer.
- (id)initWithAlpha:(CGFloat)alpha
		  blendMode:(CGBlendMode)blendMode;

// In your implementation of -renderImageFromSourceImage:withSize:, you should call this method to
// apply appearance properties. It expects you to have set up a graphics context.
- (void)applyAppearanceProperties;

// Subclasses that need to access other layers’ image data sohuld override this method.
- (UIImage *)renderedImageFromSourceImage:(UIImage *)sourceImage;

// Subclasses that render independently should override this method.
- (UIImage *)renderedImageForSize:(CGSize)size
						  atScale:(CGFloat)scale;

// Used in image caching.
- (NSDictionary *)representativeDictionary;
- (NSString *)representativeHash;
+ (id)effectWithRepresentativeDictionary:(NSDictionary *)representativeDictionary;
- (id)initWithRepresentativeDictionary:(NSDictionary *)representativeDictionary;

// Set to NO if the image effect needs to render with the image data under it and can’t be cached
// separately
+ (BOOL)canRenderIndividually;

- (void)cacheRenderedImage:(UIImage *)image;
- (UIImage *)previouslyRenderedImageForSize:(CGSize)size
									atScale:(CGFloat)scale;

// Set to NO if the class is mutable.
+ (BOOL)isImmutable;

// For image effects that maintain state, use a lock.
- (void)obtainLock;
- (void)releaseLock;

@end
